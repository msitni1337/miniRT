#include "Renderer.h"

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

t_hit cast_ray(t_scene *scene, t_ray ray, int hidden)
{
	t_object *object;
	size_t i;
	t_hit hit;
	t_hit tmp;

	i = 0;
	hit.is_valid = FALSE;
	while (i < scene->objects_count)
	{
		object = scene->objects + i;
		tmp = object->intersection(object, ray);
		if (tmp.is_valid && (hidden || !tmp.object->hidden) && (!hit.is_valid || tmp.distance < hit.distance))
			hit = tmp;
		i++;
	}
	return hit;
}