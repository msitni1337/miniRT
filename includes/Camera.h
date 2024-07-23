#ifndef CAMERA_H
#define CAMERA_H
#include "Vec3.h"

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	forward;
	t_vec3	U;
	t_vec3	V;
	float	fov;
	float	aspect_ratio;
} t_camera;

t_camera new_camera(t_vec3 origin, t_vec3 orientation, float aspect_ratio, float fov);
void calculate_camera_uv(t_camera*camera);

#endif // CAMERA_H