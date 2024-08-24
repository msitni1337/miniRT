#include "Object.h"

t_hit cap_intersection(t_vec3 cap_normal, t_vec3 cap_center, float radius, t_ray ray)
{
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
		if (vec3_magnitude(vec3_sub_vec3(hit.hit_point, cap_center)) <= radius)
			hit.is_valid = 1;
	}
	return hit;
}

t_vec3 cylinder_point_normal(t_hit hit_point)
{
	t_object *object = hit_point.object;
	t_vec3 p = vec3_sub_vec3(hit_point.hit_point, get_object_pos(object));
	float p_height = vec3_dot(p, object->normal);
	p = vec3_add_vec3(get_object_pos(object),vec3_scale(object->normal, p_height));

	return (vec3_normalize(vec3_sub_vec3(hit_point.hit_point, p)));
}

t_hit cylinder_intersection(t_object *object, t_ray ray)
{
	t_vec3 w = vec3_sub_vec3(ray.origin, get_object_pos(object));

	float a = vec3_dot(ray.dir, ray.dir) - (vec3_dot(ray.dir, object->normal) * vec3_dot(ray.dir, object->normal));
	float b = 2 * (vec3_dot(ray.dir, w) - (vec3_dot(ray.dir, object->normal) * vec3_dot(w, object->normal)));
	float c = vec3_dot(w, w) - (vec3_dot(w, object->normal) * vec3_dot(w, object->normal)) - (object->radius * object->radius);

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
		hit.normal = cylinder_point_normal(hit);
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
		hit.normal = cylinder_point_normal(hit);
	}

	t_vec3 hitpoint_vector = vec3_sub_vec3(hit.hit_point, get_object_pos(object));
	float origin_distance = vec3_dot(hitpoint_vector, object->normal);
	if (fabs(origin_distance) > object->height / 2)
	{
		if (determinant > ZERO)
		{
			float t = (-b + sqrtf(determinant)) / (2 * a);
			hit.hit_point = vec3_scale(ray.dir, t);
			hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
			hit.data = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));
			hitpoint_vector = vec3_sub_vec3(hit.hit_point, get_object_pos(object));
			origin_distance = vec3_dot(hitpoint_vector, object->normal);
			if (fabs(origin_distance) > object->height / 2)
			{
				hit.object = NULL;
				hit.data = INF;
			}
		}
	}
	t_hit cap;
	t_hit tmp_cap;
	cap = cap_intersection(object->normal, vec3_add_vec3(get_object_pos(object), vec3_scale(object->normal, object->height / 2)), object->radius, ray);
	// cap = cap_intersection(object->normal, vec3_scale(object->normal, object->params.x / 2), (object->params.y / 2), ray);
	cap.normal = object->normal;

	tmp_cap = cap_intersection(object->normal, vec3_add_vec3(get_object_pos(object), vec3_scale(object->normal, -object->height / 2)), object->radius, ray);
	tmp_cap.normal = vec3_scale(object->normal, -1.0f);

	if (vec3_magnitude(vec3_sub_vec3(tmp_cap.hit_point, ray.origin)) < vec3_magnitude(vec3_sub_vec3(cap.hit_point, ray.origin)))
	{
		if (tmp_cap.is_valid)
		{
			cap = tmp_cap;
		}
	}
	if (cap.is_valid && cap.data < hit.data)
	{
		hit.object = object;
		hit.hit_point = cap.hit_point;
		hit.data = cap.data;
		hit.normal = cap.normal;
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

	cylinder.normal = vec3_normalize(normal);
	cylinder.color = vec3_scale(color, 1.0f / 255.0f);
	cylinder.height = height_diameter.x;
	cylinder.radius = height_diameter.y / 2;

	cylinder.SRT_matrix = mat_id();
	// tmp = get_euler_rotation_matrix(normal);
	// plane.SRT_matrix = mat_mul(&tmp, &plane.SRT_matrix);
	set_object_pos(&cylinder, center);
	// plane.ISRT_matrix = mat_inv(&plane.SRT_matrix);

	return cylinder;
}