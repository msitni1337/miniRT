#include "Ray.h"

t_ray get_ray(t_camera *camera, t_vec3 pixel, t_vec3 img_size)
{
	t_ray ray;
	float x;
	float y;
	t_vec3 xU;
	t_vec3 xV;

	x = (((pixel.x / img_size.x) * 0.5) - 1) * 2;
	y = (((pixel.y / img_size.y) * 0.5) - 1) * 2;
	ray.origin = camera->origin;
	xU = vec3_scale(camera->U, x * camera->horizontal_size);
	xV = vec3_scale(camera->V, y * (camera->horizontal_size / camera->aspect_ratio));
	ray.dir = vec3_add_vec3(xU, xV);
	ray.dir = vec3_sub_vec3(ray.dir, ray.origin);
	return ray;
}
t_hit *cast_ray(t_scene *scene, t_ray ray)
{
}