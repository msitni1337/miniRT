#include "Object.h"

void cylinder_recalculate(t_object *obj)
{
	obj->anti_normal = vec3_scale(obj->normal, -1);
	obj->top_cap_center = vec3_add_vec3(obj->position, vec3_scale(obj->normal, obj->height / 2));
	obj->bottom_cap_center = vec3_add_vec3(obj->position, vec3_scale(obj->anti_normal, obj->height / 2));

	obj->orth_normal = vec3_normalize(vec3_cross(obj->normal, (t_vec3){0.0f, 0.0f, 1.0f}));
	if (vec3_magnitude(obj->orth_normal) <= ZERO)
		obj->orth_normal = vec3_normalize(vec3_cross(obj->normal, (t_vec3){0.0f, 1.0f, 0.0f}));

	obj->orth_normal2 = vec3_cross(obj->normal, obj->orth_normal);
}

t_vec4 cylinder_map_uv(t_hit hit, t_object *obj)
{
	t_vec4 map;
	t_vec3 point_vector;

	point_vector = vec3_sub_vec3(hit.hit_point, obj->position);
	map.z = obj->radius * atan2f(-vec3_dot(obj->orth_normal, point_vector), vec3_dot(obj->orth_normal2, point_vector));
	map.x = map.z / (obj->radius * PI);

	map.w = vec3_dot(obj->anti_normal, point_vector);
	map.y = map.w / (obj->height / 2);

	return map;
}

t_vec3 cylinder_point_normal(t_hit hit_point, t_object *object)
{
	t_vec3 p = vec3_sub_vec3(hit_point.hit_point, object->position);
	float p_height = vec3_dot(p, object->normal);
	p = vec3_add_vec3(object->position, vec3_scale(object->normal, p_height));

	return (vec3_normalize(vec3_sub_vec3(hit_point.hit_point, p)));
}

t_hit cylinder_intersection(t_object *object, t_ray ray)
{
	t_hit hit;

	hit.object = object;
	hit.is_valid = FALSE;
	t_vec3 w = vec3_sub_vec3(ray.origin, object->position);

	float a = vec3_dot(ray.dir, ray.dir) - (vec3_dot(ray.dir, object->normal) * vec3_dot(ray.dir, object->normal));
	float b = 2 * (vec3_dot(ray.dir, w) - (vec3_dot(ray.dir, object->normal) * vec3_dot(w, object->normal)));
	float c = vec3_dot(w, w) - (vec3_dot(w, object->normal) * vec3_dot(w, object->normal)) - (object->radius * object->radius);

	float determinant = (b * b) - (4.0f * a * c);

	if (determinant == ZERO)
	{
		float t = -b / (2 * a);
		if (t > CAM_CLIP)
		{
			// hit.object = object;
			hit.hit_point = vec3_scale(ray.dir, t);
			hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
			hit.normal = cylinder_point_normal(hit, object);
			hit.distance = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));
			hit.is_valid = TRUE;
		}
	}
	else if (determinant > ZERO)
	{
		float t = (-b - sqrtf(determinant)) / (2 * a);
		if (t <= CAM_CLIP) // near clipping plane
			t = (-b + sqrtf(determinant)) / (2 * a);
		if (t > CAM_CLIP)
		{
			// hit.object = object;
			hit.hit_point = vec3_scale(ray.dir, t);
			hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
			hit.normal = cylinder_point_normal(hit, object);
			hit.distance = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));
			hit.is_valid = TRUE;
		}
	}

	if (hit.is_valid)
	{
		t_vec3 hitpoint_vector = vec3_sub_vec3(hit.hit_point, object->position);
		float origin_distance = vec3_dot(hitpoint_vector, object->normal);
		if (fabs(origin_distance) > object->height / 2)
		{
			/*
			 * Check intersections with other side of the cylinder.
			 * This step can be optimized out by skipping this
			 * calculation as we always put caps on the end of
			 * the cylinder
			 */
			if (determinant > ZERO)
			{
				float t = (-b + sqrtf(determinant)) / (2 * a);
				hit.hit_point = vec3_scale(ray.dir, t);
				hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
				hitpoint_vector = vec3_sub_vec3(hit.hit_point, object->position);
				origin_distance = vec3_dot(hitpoint_vector, object->normal);
				if (fabs(origin_distance) > object->height / 2)
					hit.is_valid = FALSE;
				else
					hit.distance = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));
			}
			else
				hit.is_valid = FALSE;
		}
	}

	if (hit.is_valid)
		hit.uv_map = cylinder_map_uv(hit, object);

	t_hit cap;
	t_hit top_cap;
	t_hit down_cap;

	cap.is_valid = FALSE;
	top_cap = cap_intersection(object->normal, object->top_cap_center, object->radius, ray);
	top_cap.normal = object->normal;

	down_cap = cap_intersection(object->normal, object->bottom_cap_center, object->radius, ray);
	down_cap.normal = object->anti_normal;

	if (top_cap.is_valid && (!down_cap.is_valid || top_cap.distance < down_cap.distance))
		cap = top_cap;
	else if (down_cap.is_valid && (!top_cap.is_valid || down_cap.distance < top_cap.distance))
		cap = down_cap;
	if (cap.is_valid && (!hit.is_valid || cap.distance < hit.distance))
	{
		// hit.object = object;
		hit.hit_point = cap.hit_point;
		hit.normal = cap.normal;
		hit.distance = cap.distance;
		hit.uv_map = cap_map_uv(vec3_sub_vec3(cap.hit_point, object->position), object->orth_normal, object->orth_normal2, object->radius);
		hit.is_valid = TRUE;
	}
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
	cylinder_recalculate(&cylinder);

	return cylinder;
}