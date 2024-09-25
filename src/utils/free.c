#include "utils.h"

void ft_free(void *p1, void *p2, void *p3)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p2);
}

void free_textures_filenames(t_scene *scene)
{
	t_object *obj;
	size_t i;

	i = 0;
	while (i < scene->objects_count)
	{
		obj = scene->objects + i;
		ft_free(obj->texture.filename, obj->normal_map.filename, NULL);
		i++;
	}
}

void free_objects_textures(void *mlx, t_object *objs, size_t count)
{
	size_t i;

	i = 0;
	while (i < count)
	{
		if (objs[i].texture.handle)
			mlx_destroy_image(mlx, objs[i].texture.handle);
		if (objs[i].normal_map.handle)
			mlx_destroy_image(mlx, objs[i].normal_map.handle);
		i++;
	}
}
