#ifndef OBJECT_H
#define OBJECT_H
#include "Mat4x4.h"

typedef enum e_object_type
{
	OBJ_PLANE,
	OBJ_SPHERE,
	OBJ_CONE,
} t_object_type;

typedef struct s_object
{
	t_object_type type;
	t_mat4x4 SRT_matrix;
	t_mat4x4 ISRT_matrix; // Todo: Possibly not needed
	t_vec4 color;
} t_object;
#endif //SPHERE_H