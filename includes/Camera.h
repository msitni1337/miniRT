#ifndef CAMERA_H
#define CAMERA_H
#include "Vec3.h"

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	up;
	t_vec3	forward;
	t_vec3	U;
	t_vec3	V;
	float	horizontal_size;
	float	aspect_ratio;
} t_camera;

void calculate_camera_uv(t_camera*camera);

#endif // CAMERA_H