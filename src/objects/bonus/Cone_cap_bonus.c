#include "Object.h"

t_hit cone_cap_intersection(t_object *object, t_ray ray)
{
	t_hit hit;
	t_hit cap;

	hit = cone_intersection(object, ray);

	cap = cap_intersection(object->anti_normal, object->position, object->radius, ray);

	if (cap.is_valid && (!hit.is_valid || cap.distance < hit.distance))
	{
		hit.hit_point = cap.hit_point;
		hit.normal = object->anti_normal;
		hit.distance = cap.distance;
		hit.uv_map = cap_map_uv(vec3_sub_vec3(cap.hit_point, object->position), object->orth_normal, object->orth_normal2, object->radius);
		hit.is_valid = TRUE;
	}
	return hit;
}

t_object new_cone_cap(t_vec3 normal, t_vec3 center, t_vec3 height_diameter, t_vec3 color)
{
	t_object cone;

	cone = (t_object){0};
	cone.type = OBJ_CONE;
	cone.intersection = &cone_cap_intersection;
	cone.recalculate = &cone_recalculate;
	cone.position = center;
	cone.normal = vec3_normalize(normal);
	cone.height = height_diameter.x;
	cone.radius = height_diameter.y / 2;
	cone.color = vec3_scale(color, 1.0f / 255.0f);
	cone_recalculate(&cone);

	return cone;
}