#include "Mat4x4.h"
#include "Camera.h"
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

int main(int c, char **v)
{
	(void)c;
	(void)v;
	t_camera camera;
	camera.up				= vec3_i(0, 0, 1);
	camera.forward			= vec3_i(0, 1, 0);
	camera.origin			= vec3_i(0, 0, -1);
	camera.horizontal_size	= 10.0f;
	camera.aspect_ratio		= 16.0f/9.0f;
	calculate_camera_uv(&camera);
	print_vec3(camera.U);
	print_vec3(camera.V);
	return 0;
}