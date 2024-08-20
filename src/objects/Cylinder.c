#include "Object.h"

t_hit cylinder_intersection(t_object *object, t_ray ray)
{
    t_vec3 w = vec3_sub_vec3(ray.origin, get_object_pos(object));

    float a = vec3_dot(ray.dir, ray.dir) - (vec3_dot(ray.dir, object->normal) * vec3_dot(ray.dir, object->normal));
    float b = 2 * (vec3_dot(ray.dir, w) - (vec3_dot(ray.dir, object->normal) * vec3_dot(w, object->normal)));
    float c = vec3_dot(w, w) - (vec3_dot(w, object->normal) * vec3_dot(w, object->normal)) - ((object->params.y / 2) * (object->params.y / 2));

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
	}
    return hit;
}

t_vec3 cylinder_point_normal(t_hit hit_point)
{
	t_object * object = hit_point.object;
    t_vec3 p = vec3_sub_vec3(hit_point.hit_point, get_object_pos(object));
	float p_height = vec3_dot(p, object->normal); 
	p = vec3_scale(object->normal, p_height);

	return (vec3_normalize(vec3_sub_vec3(hit_point.hit_point, p)));
}

t_object new_cylinder(t_vec3 normal, t_vec3 center, t_vec3 height_diameter, t_vec3 color)
{
    t_object cylinder;
    t_mat4x4 tmp;

    cylinder.type = OBJ_CYLINDER;
    cylinder.intersection = &cylinder_intersection;
    cylinder.point_normal = &cylinder_point_normal;

    cylinder.normal = vec3_normalize(normal);
    cylinder.color = vec3_scale(color, 1.0f / 255.0f);
    cylinder.params = height_diameter;

    cylinder.SRT_matrix = mat_id();
    // tmp = get_euler_rotation_matrix(normal);
    // plane.SRT_matrix = mat_mul(&tmp, &plane.SRT_matrix);
    set_object_pos(&cylinder, center);
    // plane.ISRT_matrix = mat_inv(&plane.SRT_matrix);

    return cylinder;
}