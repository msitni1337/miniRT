#include "Ray.h"

t_ray get_ray(t_camera *camera, t_vec3 pixel, t_vec3 img_size)
{
	t_ray ray;
	t_vec3 tmp;

	pixel.x = (((pixel.x / img_size.x) * 0.5) - 1) * 2;
	pixel.y = (((pixel.y / img_size.y) * 0.5) - 1) * 2;
	ray.origin = camera->origin;
	tmp = vec3_scale(camera->U, pixel.x);
	ray.target = vec3_scale(camera->V, pixel.y);
	ray.target = vec3_add_vec3(ray.target, tmp);
	ray.target = vec3_add_vec3(ray.target, ray.origin);
	ray.dir = vec3_sub_vec3(ray.target, ray.origin);
	ray.dir = vec3_normalize(ray.dir);
	return ray;
}

t_hits cast_ray(t_scene *scene, t_ray ray)
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
	float radius_sq = (float)scene->objects.object_data;
	t_vec3 map_origine = mat_mul_vec3(&scene->objects.ISRT_matrix, &ray.origin);
	t_vec3 map_direct = mat_mul_vec3(&scene->objects.ISRT_matrix, &ray.dir);

	float b = 2 * (map_origine.x * map_direct.x + map_origine.y * map_direct.y + map_origine.z * map_direct.z);
	float c = (map_origine.x * map_origine.x + map_origine.y * map_origine.y + map_origine.z * map_origine.z - radius_sq);
	float determinant = b * b - 4 * c;
	t_hits hit;
	hit.count = 0;
	if (determinant < 0.0)
	{
		return hit;
	}
	else if (determinant == 0.0)
	{
		float t = -b / 2;
		if (t < 0.1) // near clipping plane
			return hit;
		hit.count = 1;

		hit.hit_point = vec3_scale(map_direct, t);
		hit.hit_point = vec3_add_vec3(hit.hit_point, map_origine);
		hit.hit_point = mat_mul_vec3(&scene->objects.SRT_matrix, &hit.hit_point);
	}
	else if
	{
		float t = (-b + sqrt(b * b - 4 * c)) / 2;
		if (t < 0.1) // near clipping plane
			return hit;
		hit.count = 1;
		hit.hit_point = vec3_scale(map_direct, t);
		hit.hit_point = vec3_add_vec3(hit.hit_point, map_origine);
		hit.hit_point = mat_mul_vec3(&scene->objects.SRT_matrix, &hit.hit_point);
	}
}