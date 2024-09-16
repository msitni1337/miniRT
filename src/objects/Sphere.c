#include "Object.h"
#include <stdio.h>

void sphere_recalculate(t_object *object)
{
}

t_vec4 sphere_map_uv(t_hit hit, t_object *obj)
{
	t_vec4 map;
	t_vec3 point_vector;

	point_vector = vec3_sub_vec3(hit.hit_point, obj->position);
	map.x = atan2f(point_vector.y, point_vector.x) / PI;
	map.z = map.x * (obj->radius);
	map.w = vec3_dot(point_vector, (t_vec3){0.0f, 0.0f, -1.0f});
	map.y = map.w / (obj->radius);
	return map;
}

t_hit sphere_intersection(t_object *object, t_ray ray)
{
	/*
		(r.a.x + t r.d.x - p.x)² + (r.a.y + t r.d.y - p.y)² + (r.a.z + t r.d.z - p.z)²  = r²
		let r.a - p = w;

		(w.x + t r.d.x)² = t² r.d.x² + t * 2 * w.x * r.d.x +  w.x²
		(w.y + t r.d.y)² = t² r.d.y² + t * 2 * w.y * r.d.y +  w.y²
		(w.z + t r.d.z)² = t² r.d.z² + t * 2 * w.z * r.d.z +  w.z²


		a = (rdx² + rdy² + rdz²) = > this always will be 1 cause ray.dir is normalized
		b = 2 * (w.x * rdx + w.y * rdy + w.z * rdz) = 2 * dot(w, r.d)
		c = (w.x² + w.y² + w.z² - r²) = dot(w,w) - r² << Can be calculated & stored once instead of always calculating it hum ...
		t = (-b +/- sqrtf(b² - 4 a c)) / (2 * a)
	*/
	t_hit hit;
	hit.object = object;
	hit.is_valid = FALSE;

	float radius_sq = object->radius * object->radius;
	t_vec3 w = vec3_sub_vec3(ray.origin, object->position);

	float b = 2 * vec3_dot(w, ray.dir);
	float c = vec3_dot(w, w) - radius_sq;

	float determinant = (b * b) - (4.0f * c);

	if (determinant == ZERO)
	{
		float t = -b / 2;
		if (t > CAM_CLIP) // near clipping plane
		{
			hit.is_valid = TRUE;
			hit.hit_point = vec3_scale(ray.dir, t);
			hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
			hit.distance = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));
			hit.normal = vec3_normalize(vec3_sub_vec3(hit.hit_point, object->position));
		}
	}
	else if (determinant > ZERO)
	{
		float t = (-b - sqrtf(determinant)) / 2;
		if (t <= CAM_CLIP) // near clipping plane
			t = (-b + sqrtf(determinant)) / 2;
		if (t > CAM_CLIP)
		{
			hit.is_valid = TRUE;
			hit.hit_point = vec3_scale(ray.dir, t);
			hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
			hit.distance = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));
			hit.normal = vec3_normalize(vec3_sub_vec3(hit.hit_point, object->position));
		}
	}
	if (hit.is_valid)
		hit.uv_map = sphere_map_uv(hit, object);
	return hit;
}

t_object new_sphere(t_vec3 pos, float radius, t_vec3 color)
{
	t_object sphere;

	sphere = (t_object){0};
	sphere.type = OBJ_SPHERE;
	sphere.intersection = &sphere_intersection;
	sphere.recalculate = &sphere_recalculate;
	sphere.position = pos;
	sphere.radius = radius;
	sphere.color = vec3_scale(color, 1.0f / 255.0f);
	return sphere;
}