#ifndef SPHERE_H
#define SPHERE_H
#include "Mat4x4.h"
typedef struct s_sphere
{
	t_mat4x4 SRT_matrix;
	t_mat4x4 ISRT_matrix; // Todo: Possibly not needed
	t_vec4 color;
} t_sphere;
#endif //SPHERE_H