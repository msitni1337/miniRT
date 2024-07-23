#include "Ray.h"

t_ray get_ray(t_camera *camera, t_vec3 pixel, t_vec3 img_size)
{
	t_ray ray;
	t_vec3 tmp;

	pixel.x		= (((pixel.x / img_size.x) * 0.5) - 1) * 2;
	pixel.y		= (((pixel.y / img_size.y) * 0.5) - 1) * 2;
	ray.origin	= camera->origin;
	tmp			= vec3_scale(camera->U, pixel.x);
	ray.target	= vec3_scale(camera->V, pixel.y);
	ray.target	= vec3_add_vec3(ray.target, tmp);
	ray.target	= vec3_add_vec3(ray.target, ray.origin);
	ray.dir 	= vec3_sub_vec3(ray.target, ray.origin);
	return ray;
}
/*
t_hit *cast_ray(t_scene *scene, t_ray ray)
{
}
*/