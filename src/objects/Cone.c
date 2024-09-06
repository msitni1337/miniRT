#include "Object.h"

t_hit cone_cap_intersection(t_vec3 cap_normal, t_vec3 cap_center, float radius, t_ray ray)
{
	/*
	float dot_na = vec3_dot(cap_normal, ray.origin);
	float dot_nd = vec3_dot(cap_normal, ray.dir);
	float dot_np = vec3_dot(cap_normal, cap_center);

	t_hit hit;
	hit.is_valid = 0;
	if (fabs(dot_nd) > ZERO)
	{
		float t = (dot_np - dot_na) / dot_nd;
		if (t <= CAM_CLIP)
			return hit;
		hit.hit_point = vec3_scale(ray.dir, t);
		hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
		hit.data = vec3_magnitude(vec3_sub_vec3(hit.hit_point, ray.origin));
		if (vec3_magnitude(vec3_sub_vec3(hit.hit_point, cap_center)) < radius)
			hit.is_valid = 1;
	}
	return hit;
	*/
	return (t_hit){0};
}

t_vec3 cone_point_normal(t_hit hit_point)
{
	/*
	t_object *object = hit_point.object;
	t_vec3 p = vec3_sub_vec3(hit_point.hit_point, get_object_pos(object));
	// float p_height = vec3_dot(p, object->normal);
	// p = vec3_add_vec3(get_object_pos(object),vec3_scale(object->normal, p_height));

	return (vec3_normalize(p));
	*/
	return (t_vec3){0};
}

t_hit cone_intersection(t_object *object, t_ray ray)
{
	/*
	t_vec3 tip = vec3_add_vec3(get_object_pos(object), vec3_scale(object->normal, object->height)); // can be optimize out
	t_vec3 w = vec3_sub_vec3(ray.origin, tip);

	float r = object->radius;
	float tip_dist = vec3_magnitude(vec3_scale(object->normal, object->height));
	float m = (r * r) / (tip_dist * tip_dist);

	float a = vec3_dot(ray.dir, ray.dir) - m * (vec3_dot(ray.dir, object->normal) * vec3_dot(ray.dir, object->normal)) - (vec3_dot(ray.dir, object->normal) * vec3_dot(ray.dir, object->normal));
	float b = 2 * (vec3_dot(ray.dir, w) - m * (vec3_dot(ray.dir, object->normal) * vec3_dot(w, object->normal)) - (vec3_dot(ray.dir, object->normal) * vec3_dot(w, object->normal)));
	float c = vec3_dot(w, w) - m * (vec3_dot(w, object->normal) * vec3_dot(w, object->normal)) - (vec3_dot(w, object->normal) * vec3_dot(w, object->normal));

	float determinant = (b * b) - (4.0f * a * c);
	t_hit hit;
	hit.object = NULL;
	hit.data = INF;
	if (determinant == ZERO)
	{
		float t = -b / (2 * a);
		if (t <= CAM_CLIP) // near clipping plane
			return hit;
		hit.object = object;
		hit.hit_point = vec3_scale(ray.dir, t);
		hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
		hit.data = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));
		hit.normal = cone_point_normal(hit);
	}
	else if (determinant > ZERO)
	{
		float t = (-b - sqrtf(determinant)) / (2 * a);
		if (t <= CAM_CLIP) // near clipping plane
		{
			t = (-b + sqrtf(determinant)) / (2 * a);
			if (t <= CAM_CLIP)
				return hit;
		}
		hit.object = object;
		hit.hit_point = vec3_scale(ray.dir, t);
		hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
		hit.data = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));
		hit.normal = cone_point_normal(hit);
	}
	*/

	/*
	 * Check intersections with other side of the cone.
	 * This step can be optimized out by skipping this
	 * calculation as we always put caps on the end of
	 * the cone
	 */
	/*
		t_vec3 hitpoint_vector = vec3_sub_vec3(hit.hit_point, get_object_pos(object));
		float origin_distance = vec3_dot(hitpoint_vector, object->normal);
		if (origin_distance < ZERO || origin_distance > object->height)
		{
			if (determinant > ZERO)
			{
				float t = (-b + sqrtf(determinant)) / (2 * a);
				hit.hit_point = vec3_scale(ray.dir, t);
				hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
				hit.data = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));

				hitpoint_vector = vec3_sub_vec3(hit.hit_point, get_object_pos(object));
				origin_distance = vec3_dot(hitpoint_vector, object->normal);
				if (origin_distance < ZERO || origin_distance > object->height)
				{
					hit.object = NULL;
					hit.data = INF;
				}
			}
		}

		t_hit cap;
		cap.normal = vec3_scale(object->normal, -1.0f);
		cap = cone_cap_intersection(cap.normal, get_object_pos(object), object->radius, ray);

		if (cap.is_valid && cap.data < hit.data)
		{
			hit.object = object;
			hit.hit_point = cap.hit_point;
			hit.data = cap.data;
			hit.normal = cap.normal;
		}
		return hit;
	*/
	return (t_hit){0};
}

t_object new_cone(t_vec3 normal, t_vec3 center, t_vec3 height_diameter, t_vec3 color)
{
	t_object cone;
	t_mat4x4 tmp;

	cone.type = OBJ_CONE;
	cone.intersection = &cone_intersection;
	// cylinder.point_normal = &cylinder_point_normal;

	cone.normal = vec3_normalize(normal);
	cone.color = vec3_scale(color, 1.0f / 255.0f);
	cone.height = height_diameter.x;
	cone.radius = height_diameter.y / 2;

	// cone.SRT_matrix = mat_id();
	// tmp = get_euler_rotation_matrix(normal);
	// plane.SRT_matrix = mat_mul(&tmp, &plane.SRT_matrix);
	//set_object_pos(&cone, center);
	// plane.ISRT_matrix = mat_inv(&plane.SRT_matrix);

	return cone;
}