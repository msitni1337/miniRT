#ifndef UTILS_H
#define UTILS_H
#include "Object.h"
#include <stdlib.h>

void ft_free(void *p1, void *p2, void *p3);
void *free_till(char **ptr, int index);
void free_textures_filenames(t_scene* scene);
void free_objects_textures(void *mlx, t_object *objs, size_t count);

#endif