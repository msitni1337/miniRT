#include "Ray.h"

t_ray get_ray(t_camera *camera, t_vec3 pixel, t_vec3 img_size)
{
	t_ray ray;
	t_vec3 tmp;

	pixel.x = ((pixel.x / img_size.x) - 0.5) * 2;
	pixel.y = ((pixel.y / img_size.y) - 0.5) * 2;
	ray.origin = camera->origin;
	
	ray.target = vec3_add_vec3(ray.origin, camera->forward); 
	
	tmp = vec3_scale(camera->U, pixel.x);
	ray.target = vec3_add_vec3(ray.target, tmp);

	tmp = vec3_scale(camera->V, pixel.y);
	ray.target = vec3_add_vec3(ray.target, tmp);


	ray.dir = vec3_sub_vec3(ray.target, ray.origin);
	ray.dir = vec3_normalize(ray.dir);
	return ray;
}
