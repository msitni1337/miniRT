/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:34 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:16:48 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.h"

void cylinder_recalculate(t_object *obj)
{
	obj->anti_normal = vec3_scale(obj->normal, -1);
	obj->top_cap_center = vec3_add_vec3(obj->position, vec3_scale(obj->normal, obj->height / 2));
	obj->bottom_cap_center = vec3_add_vec3(obj->position, vec3_scale(obj->anti_normal, obj->height / 2));
}

t_vec4 cylinder_map_uv(t_hit hit, t_object *obj)
{
	t_vec4 map;
	t_vec3 point_vector;

	point_vector = vec3_sub_vec3(hit.hit_point, obj->position);
	map.z = obj->radius * atan2f(-vec3_dot(obj->orth_normal, point_vector), vec3_dot(obj->orth_normal2, point_vector));
	map.x = map.z / (obj->radius * PI);
	map.x = map.x * 0.5f + 0.5f;

	map.w = vec3_dot(obj->anti_normal, point_vector);
	map.y = map.w / (obj->height / 2);
	map.y = map.y * 0.5f + 0.5f;

	return map;
}

t_vec3 cylinder_point_normal(t_hit hit_point, t_object *object)
{
	t_vec3 p = vec3_sub_vec3(hit_point.hit_point, object->position);
	float p_height = vec3_dot(p, object->normal);
	p = vec3_add_vec3(object->position, vec3_scale(object->normal, p_height));

	return (vec3_normalize(vec3_sub_vec3(hit_point.hit_point, p)));
}

t_quad_eq calculate_cylinder_quad(t_object *obj, t_ray ray)
{
	t_vec3 w;
	t_quad_eq eq;
	float dot_rdn;
	float dot_wn;

	w = vec3_sub_vec3(ray.origin, obj->position);
	dot_rdn = vec3_dot(ray.dir, obj->normal);
	dot_wn = vec3_dot(w, obj->normal);
	eq.a = vec3_dot(ray.dir, ray.dir) - (dot_rdn * dot_rdn);
	eq.b = 2 * (vec3_dot(ray.dir, w) - (dot_rdn * dot_wn));
	eq.c = vec3_dot(w, w) - (dot_wn * dot_wn) - (obj->radius * obj->radius);
	eq.det = (eq.b * eq.b) - (4.0f * eq.a * eq.c);
	return eq;
}

void chop_cylinder(t_quad_eq eq, t_hit *hit, t_object *obj, t_ray ray)
{
	t_vec3 hitpoint_vector;
	float origin_distance;
	float t;

	hitpoint_vector = vec3_sub_vec3(hit->hit_point, obj->position);
	origin_distance = vec3_dot(hitpoint_vector, obj->normal);
	t = eq.t;
	if (fabs(origin_distance) > obj->height / 2)
	{
		/*
		 * Check intersections with other side of the cylinder.
		 * This step can be optimized out by skipping this
		 * calculation as we always put caps on the end of
		 * the cylinder
		 */
		if (eq.det > ZERO)
		{
			t = (-eq.b + sqrtf(eq.det)) / (2 * eq.a);
			if (eq.t != t)
			{
				hit->hit_point = vec3_scale(ray.dir, t);
				hit->hit_point = vec3_add_vec3(hit->hit_point, ray.origin);
				hitpoint_vector = vec3_sub_vec3(hit->hit_point, obj->position);
				origin_distance = vec3_dot(hitpoint_vector, obj->normal);
				hit->distance = vec3_magnitude(vec3_sub_vec3(ray.origin, hit->hit_point));
			}
		}
		if (eq.t == t || fabs(origin_distance) > obj->height / 2)
			hit->is_valid = FALSE;
	}
}

void cylinder_caps(t_hit *hit, t_object *obj, t_ray ray)
{
	t_hit cap;
	t_hit top_cap;
	t_hit down_cap;

	cap.is_valid = FALSE;
	top_cap = cap_intersection(obj->normal, obj->top_cap_center, obj->radius, ray);
	top_cap.normal = obj->normal;
	down_cap = cap_intersection(obj->normal, obj->bottom_cap_center, obj->radius, ray);
	down_cap.normal = obj->anti_normal;
	if (top_cap.is_valid && (!down_cap.is_valid || top_cap.distance < down_cap.distance))
		cap = top_cap;
	else if (down_cap.is_valid && (!top_cap.is_valid || down_cap.distance < top_cap.distance))
		cap = down_cap;
	if (cap.is_valid && (!hit->is_valid || cap.distance < hit->distance))
	{
		hit->hit_point = cap.hit_point;
		hit->normal = cap.normal;
		hit->distance = cap.distance;
		hit->uv_map = cap_map_uv(vec3_sub_vec3(cap.hit_point, obj->position), obj->orth_normal, obj->orth_normal2, obj->radius);
		hit->is_valid = TRUE;
	}
}

t_hit cylinder_intersection(t_object *object, t_ray ray)
{
	t_quad_eq eq;
	t_hit hit;

	hit.object = object;
	hit.is_valid = FALSE;

	eq = calculate_cylinder_quad(object, ray);
	solve_quad_eq(eq, &hit, ray);
	if (hit.is_valid)
		chop_cylinder(eq, &hit, object, ray);
	if (hit.is_valid)
	{
		hit.normal = cylinder_point_normal(hit, object);
		hit.uv_map = cylinder_map_uv(hit, object);
	}
	cylinder_caps(&hit, object, ray);
	return hit;
}

t_object new_cylinder(t_vec3 normal, t_vec3 center, t_vec3 height_diameter, t_vec3 color)
{
	t_object cylinder;

	cylinder = (t_object){0};
	cylinder.type = OBJ_CYLINDER;
	cylinder.intersection = &cylinder_intersection;
	cylinder.recalculate = &cylinder_recalculate;
	cylinder.position = center;
	cylinder.normal = vec3_normalize(normal);
	cylinder.height = height_diameter.x;
	cylinder.radius = height_diameter.y / 2;
	cylinder.color = vec3_scale(color, 1.0f / 255.0f);
	cylinder.orth_normal = vec3_normalize(vec3_cross(cylinder.normal, (t_vec3){0.0f, 1.0f, 0.0f}));
	if (vec3_magnitude(cylinder.orth_normal) <= ZERO)
		cylinder.orth_normal = vec3_normalize(vec3_cross(cylinder.normal, (t_vec3){0.0f, 0.0f, 1.0f}));
	cylinder.orth_normal2 = vec3_cross(cylinder.normal, cylinder.orth_normal);
	cylinder_recalculate(&cylinder);
	return cylinder;
}