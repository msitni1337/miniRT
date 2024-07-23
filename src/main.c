#include "Mat4x4.h"
#include "Renderer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int c, char **v)
{
	(void)c;
	(void)v;
	/*
	t_renderer renderer;
	renderer.scene.camera = new_camera((t_vec3) {0,-1,0},(t_vec3) {0,1,0}, 720.0f/1280.0f, 160);
	t_ray ray = get_ray(&renderer.scene.camera, (t_vec3) {0, 0}, (t_vec3) {1280, 720});

	printf("renderer.scene.camera.origin: \n");
	print_vec3(renderer.scene.camera.origin);
	printf("renderer.scene.camera.forward: \n");
	print_vec3(renderer.scene.camera.forward);
	printf("renderer.scene.camera.U: \n");
	print_vec3(renderer.scene.camera.U);
	printf("renderer.scene.camera.V: \n");
	print_vec3(renderer.scene.camera.V);
	printf("ray.origin: \n");
	print_vec3(ray.origin);
	printf("ray.target: \n");
	print_vec3(ray.target);
	printf("ray.dir: \n");
	print_vec3(ray.dir);
	*/
	t_mat4x4 m1 = mat_id();
	t_mat4x4 m2 = mat_id();

	*mat_at(&m1, 1, 2) = 17;
	*mat_at(&m1, 3, 2) = 3;
	*mat_at(&m1, 0, 2) = 5;

	t_mat4x4 m3 = mat_mul(&m1, &m2);

	printf("m1: \n");
	mat_print(&m1);
	printf("m2: \n");
	mat_print(&m2);
	printf("m3: \n");
	mat_print(&m3);
	return 0;
}