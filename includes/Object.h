#ifndef OBJECT_H
#define OBJECT_H
#include "Ray.h"

typedef enum e_object_type
{
	OBJ_PLANE,
	OBJ_SPHERE,
	OBJ_CONE,
} t_object_type;

typedef struct s_object
{
	t_object_type type;
	t_hits (*intersection)(t_object *object, t_ray ray);
	t_mat4x4 SRT_matrix;
	t_mat4x4 ISRT_matrix;
	t_vec3 color;
	float object_data;
} t_object;
#endif //SPHERE_H