#include "Object.h"

void cone_recalculate(t_object *obj)
{
	obj->anti_normal = vec3_scale(obj->normal, -1);

	obj->orth_normal = vec3_normalize(vec3_cross(obj->normal, (t_vec3){0.0f, 0.0f, 1.0f}));
	if (vec3_magnitude(obj->orth_normal) <= ZERO)
		obj->orth_normal = vec3_normalize(vec3_cross(obj->normal, (t_vec3){0.0f, 1.0f, 0.0f}));

	obj->orth_normal2 = vec3_cross(obj->normal, obj->orth_normal);
	obj->cone_tip = vec3_add_vec3(obj->position, vec3_scale(obj->normal, obj->height));
}

t_vec4 cone_map_uv(t_hit hit, t_object *obj)
{
	t_vec4 map;
	t_vec3 point_vector;

	point_vector = vec3_sub_vec3(hit.hit_point, obj->position);
	map.z = obj->radius * atan2f(vec3_dot(obj->orth_normal, point_vector), vec3_dot(obj->orth_normal2, point_vector));
	map.x = map.z / (obj->radius * PI) ;

	map.w = vec3_dot(obj->normal, point_vector);
	map.y = map.w / obj->height;
	return map;
}

t_hit cone_intersection(t_object *object, t_ray ray)
{
	t_hit hit;

	hit.object = object;
	hit.is_valid = FALSE;

	t_vec3 w = vec3_sub_vec3(ray.origin, object->cone_tip);

	float r = object->radius;
	float tip_dist = vec3_magnitude(vec3_scale(object->normal, object->height));
	float m = (r * r) / (tip_dist * tip_dist);

	float a = vec3_dot(ray.dir, ray.dir) - m * (vec3_dot(ray.dir, object->normal) * vec3_dot(ray.dir, object->normal)) - (vec3_dot(ray.dir, object->normal) * vec3_dot(ray.dir, object->normal));
	float b = 2 * (vec3_dot(ray.dir, w) - m * (vec3_dot(ray.dir, object->normal) * vec3_dot(w, object->normal)) - (vec3_dot(ray.dir, object->normal) * vec3_dot(w, object->normal)));
	float c = vec3_dot(w, w) - m * (vec3_dot(w, object->normal) * vec3_dot(w, object->normal)) - (vec3_dot(w, object->normal) * vec3_dot(w, object->normal));

	float determinant = (b * b) - (4.0f * a * c);

	if (determinant == ZERO)
	{
		float t = -b / (2 * a);
		if (t > CAM_CLIP) // near clipping plane
		{
			hit.hit_point = vec3_scale(ray.dir, t);
			hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
			hit.normal = vec3_normalize(vec3_sub_vec3(hit.hit_point, object->position));
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
			hit.hit_point = vec3_scale(ray.dir, t);
			hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
			hit.normal = vec3_normalize(vec3_sub_vec3(hit.hit_point, object->position));
			hit.distance = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));
			hit.is_valid = TRUE;
		}
	}

	if (hit.is_valid)
	{
		t_vec3 hitpoint_vector = vec3_sub_vec3(hit.hit_point, object->position);
		float origin_distance = vec3_dot(hitpoint_vector, object->normal);
		if (origin_distance < ZERO || origin_distance > object->height)
		{
			/*
			 * Check intersections with other side of the cone.
			 * This step can be optimized out by skipping this
			 * calculation as we always put caps on the end of
			 * the cone
			 */
			if (determinant > ZERO)
			{
				float t = (-b + sqrtf(determinant)) / (2 * a);
				hit.hit_point = vec3_scale(ray.dir, t);
				hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);

				hitpoint_vector = vec3_sub_vec3(hit.hit_point, object->position);
				origin_distance = vec3_dot(hitpoint_vector, object->normal);
				if (origin_distance < ZERO || origin_distance > object->height)
					hit.is_valid = FALSE;
				else
					hit.distance = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));
			}
			else
				hit.is_valid = FALSE;
		}
	}

	if (hit.is_valid)
		hit.uv_map = cone_map_uv(hit, object);

	t_hit cap;
	cap = cap_intersection(object->anti_normal, object->position, object->radius, ray);

	if (cap.is_valid && (!hit.is_valid || cap.distance < hit.distance))
	{
		hit.hit_point = cap.hit_point;
		hit.normal = object->anti_normal;
		hit.distance = cap.distance;
		hit.uv_map = plane_map_uv(vec3_sub_vec3(cap.hit_point, object->position), object->orth_normal, object->orth_normal2);
		hit.is_valid = TRUE;
	}
	return hit;
}

t_object new_cone(t_vec3 normal, t_vec3 center, t_vec3 height_diameter, t_vec3 color)
{
	t_object cone;

	cone = (t_object){0};
	cone.type = OBJ_CONE;
	cone.intersection = &cone_intersection;
	cone.recalculate = &cone_recalculate;
	cone.position = center;
	cone.normal = vec3_normalize(normal);
	cone.height = height_diameter.x;
	cone.radius = height_diameter.y / 2;
	cone.color = vec3_scale(color, 1.0f / 255.0f);
	cone_recalculate(&cone);

	return cone;
}