#include "Object.h"

t_hit cap_intersection(t_vec3 cap_normal, t_vec3 cap_center, float radius, t_ray ray)
{
	float dot_na = vec3_dot(cap_normal, ray.origin);
	float dot_nd = vec3_dot(cap_normal, ray.dir);
	float dot_np = vec3_dot(cap_normal, cap_center);

	t_hit hit;
	hit.is_valid = FALSE;
	if (fabs(dot_nd) > ZERO)
	{
		float t = (dot_np - dot_na) / dot_nd;
		if (t <= CAM_CLIP)
			return hit;
		hit.hit_point = vec3_scale(ray.dir, t);
		hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
		hit.distance = vec3_magnitude(vec3_sub_vec3(hit.hit_point, ray.origin));
		if (vec3_magnitude(vec3_sub_vec3(hit.hit_point, cap_center)) <= radius)
			hit.is_valid = TRUE;
	}
	return hit;
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

	/*
	 * Check intersections with other side of the cylinder.
	 * This step can be optimized out by skipping this
	 * calculation as we always put caps on the end of
	 * the cylinder
	 */
	if (hit.is_valid)
	{
		t_vec3 hitpoint_vector = vec3_sub_vec3(hit.hit_point, object->position);
		float origin_distance = vec3_dot(hitpoint_vector, object->normal);
		if (fabs(origin_distance) > object->height / 2)
		{
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
	
	t_hit cap;
	t_hit top_cap;
	t_hit down_cap;

	cap.is_valid = FALSE;
	top_cap = cap_intersection(object->normal, vec3_add_vec3(object->position, vec3_scale(object->normal, object->height / 2)), object->radius, ray);
	top_cap.normal = object->normal;

	down_cap = cap_intersection(object->normal, vec3_add_vec3(object->position, vec3_scale(object->normal, -object->height / 2)), object->radius, ray);
	down_cap.normal = vec3_scale(object->normal, -1.0f);

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
		hit.is_valid = TRUE;
	}
	return hit;
}

t_object new_cylinder(t_vec3 normal, t_vec3 center, t_vec3 height_diameter, t_vec3 color)
{
	t_object cylinder;
	t_mat4x4 tmp;

	cylinder.type = OBJ_CYLINDER;
	cylinder.intersection = &cylinder_intersection;
	// cylinder.point_normal = &cylinder_point_normal;

	cylinder.position = center;
	cylinder.normal = vec3_normalize(normal);
	cylinder.color = vec3_scale(color, 1.0f / 255.0f);
	cylinder.height = height_diameter.x;
	cylinder.radius = height_diameter.y / 2;

	cylinder.SRT_matrix = mat_id();
	// tmp = get_euler_rotation_matrix(normal);
	// plane.SRT_matrix = mat_mul(&tmp, &plane.SRT_matrix);
	// set_object_pos(&cylinder, center);
	// plane.ISRT_matrix = mat_inv(&plane.SRT_matrix);

	return cylinder;
}