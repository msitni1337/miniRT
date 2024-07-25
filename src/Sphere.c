#include "Object.h"
#include <stdio.h>

t_hit sphere_intersection(t_object *object, t_ray ray)
{
	/*
		(r.a.x + t r.d.x)² + (r.a.y + t r.d.y)² + (r.a.z + t r.d.z)²  = r²
		(r.a.x + t r.d.x)² + (r.a.y + t r.d.y)² + (r.a.z + t r.d.z)²  = r²

		(r.a.x + t r.d.x)² = rax² + t² rdx² + 2 t * rax * rdx
		(r.a.y + t r.d.y)² = ray² + t² rdy² + 2 t * ray * rdy
		(r.a.z + t r.d.z)² = raz² + t² rdz² + 2 t * raz * rdz

		rax² + t² rdx² + 2 t *  rax * rdx + ray² + t² rdy² + 2 t *  ray * rdy + raz² + t² rdz² + 2 t *  raz * rdz - r = 0
		t² (rdx² + rdy² + rdz²) + 2 t (rax * rdx + ray * rdy + raz * rdz) + (rax² + ray² + raz² - r²) = 0

		a = (rdx² + rdy² + rdz²) = > this always will be 1 cause ray.dir is normalized
		b = 2 * (rax * rdx + ray * rdy + raz * rdz)
		c = (rax² + ray² + raz² - r²) << Can be calculated & stored once instead of always calculating it hum ...

		t = (-b +/- sqrt(b² - 4 a c)) / (2 * a)
	*/

 if(ray.target.x == 0 && ray.target.y == 0 && ray.target.z == 0)
 {
	printf("ray.origin\n");
	print_vec3(ray.origin);
	printf("ray.target\n");
	print_vec3(ray.target);
	printf("ray.dir\n");
	print_vec3(ray.dir);
 }

	float radius_sq = object->object_data * object->object_data;
	t_vec3 map_origine = mat_mul_vec3(&object->ISRT_matrix, &ray.origin);
	t_vec3 map_target = mat_mul_vec3(&object->ISRT_matrix, &ray.target);
	t_vec3 map_direct = vec3_sub_vec3(map_target, map_origine);

	map_direct = vec3_normalize(map_direct);

	float b = 2 * (map_origine.x * map_direct.x + map_origine.y * map_direct.y + map_origine.z * map_direct.z);
	float c = (map_origine.x * map_origine.x + map_origine.y * map_origine.y + map_origine.z * map_origine.z - radius_sq);
	float determinant = (b * b) - (4.0f  * c);
	
	t_hit hit;
	hit.count = 0;
	if (determinant == 0.0)
	{
		float t = -b / 2;
		if (t < 0.1) // near clipping plane
			return hit;
		hit.count = 1;
		hit.hit_point = vec3_scale(map_direct, t);
		hit.hit_point = vec3_add_vec3(hit.hit_point, map_origine);
		hit.hit_point = mat_mul_vec3(&object->SRT_matrix, &hit.hit_point);
	}
	else if (determinant > 0.0)
	{
		float t = (-b + sqrt(determinant)) / 2;
		if (t < 0.1) // near clipping plane
			return hit;
		hit.count = 1;
		hit.hit_point = vec3_scale(map_direct, t);
		hit.hit_point = vec3_add_vec3(hit.hit_point, map_origine);
		hit.hit_point = mat_mul_vec3(&object->SRT_matrix, &hit.hit_point);
	}
	if(ray.target.x == 0 && ray.target.y == 0 && ray.target.z == 0)
		printf("determinant: %d\n", determinant);
	return hit;
}

t_object new_sphere(t_vec3 pos, float radius, t_vec3 color)
{
	t_object sphere;

	sphere.type = OBJ_SPHERE;
	sphere.color = vec3_scale(color, 1.0f / 255.0f);
	sphere.intersection = &sphere_intersection;
	sphere.object_data = radius;
	sphere.SRT_matrix = mat_id();
	set_object_pos(&sphere.SRT_matrix, pos);
	sphere.ISRT_matrix = mat_inv(&sphere.SRT_matrix);
	return sphere;
}