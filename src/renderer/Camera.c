#include "Camera.h"

void calculate_camera_uv(t_camera*camera)
{
	camera->forward = vec3_normalize(camera->forward);
	// Constructing uvs vectors
	camera->U = vec3_cross(camera->forward, (t_vec3){0.0f, 0.0f, 1.0f});
	camera->U = vec3_scale(camera->U, sinf((camera->fov / 180.0f) * (PI / 2.0f)));
	
	// scaling uvs vectors
	camera->V = vec3_cross(camera->U, camera->forward);
	camera->V = vec3_scale(camera->V, camera->aspect_ratio);
}

t_camera new_camera(t_vec3 origin, t_vec3 orientation, float aspect_ratio, float fov)
{
	t_camera camera;

	camera.origin = origin;
	camera.forward = vec3_normalize(orientation);
	camera.aspect_ratio = aspect_ratio;
	camera.fov = fov;
	calculate_camera_uv(&camera);
	return camera;
}