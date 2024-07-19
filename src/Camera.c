#include "Camera.h"
void calculate_camera_uv(t_camera*camera)
{
	t_vec3 forward_normalized;

	forward_normalized = vec3_normalize(camera->forward);
	camera->U = vec3_cross(camera->up,
				forward_normalized);
	camera->V = vec3_cross(camera->U, forward_normalized); 
}