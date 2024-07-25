#include "Mat4x4.h"
#include "Renderer.h"
#include <stdio.h>
#include <stdlib.h>

void print_camera_value(t_camera camera)
{
	printf("camera.origin: \n");
	print_vec3(camera.origin);
	printf("camera.forward: \n");
	print_vec3(camera.forward);
	printf("camera.U: \n");
	print_vec3(camera.U);
	printf("camera.V: \n");
	print_vec3(camera.V);
	printf("camera.aspect_ratio: %f\n", camera.aspect_ratio);
}
void print_object_value(t_object object)
{
	printf("object.SRT_matrix: \n");
	mat_print(object.SRT_matrix.data, 4);
	printf("object.ISRT_matrix: \n");
	mat_print(object.ISRT_matrix.data, 4);
	printf("object.color: \n");
	print_vec3(object.color);
	printf("object.object_data: %f\n", object.object_data);
}
int key_hook(int key, t_renderer *renderer)
{
	printf("key pressed: %d\n",key);
	switch (key)
	{
	case KEY_UP:
		renderer->scene.camera.origin.y += 0.1f;
		break;
	case KEY_DOWN:
		renderer->scene.camera.origin.y -= 0.1f;
		break;
	case KEY_LEFT:
		renderer->scene.camera.origin.x -= 0.1f;
		break;
	case KEY_RIGHT:
		renderer->scene.camera.origin.x += 0.1f;
		break;
	default:
		break;
	}
	return 0;
}
int main(int c, char **v)
{
	(void)c;
	(void)v;

	t_renderer renderer;

	renderer.mlx_context = mlx_init();
	if (renderer.mlx_context == NULL)
	{
		printf("MLX INIT FAILED.");
		return 1;
	}
	renderer.win_width = 1280;
	renderer.win_height = 720;
	renderer.window = mlx_new_window(renderer.mlx_context, renderer.win_width, renderer.win_height, WIN_TITLE);
	if (renderer.window == NULL)
	{
		printf("MLX WINDOW INIT FAILED.");
		return 1;
	}
	renderer.mlx_texture.width = renderer.win_width;
	renderer.mlx_texture.height = renderer.win_height;
	renderer.mlx_texture.handle = mlx_new_image(renderer.mlx_context, renderer.mlx_texture.width, renderer.mlx_texture.height);
	if (renderer.mlx_texture.handle == NULL)
	{
		printf("MLX IMG INIT FAILED.");
		return 1;
	}
	renderer.mlx_texture.data = mlx_get_data_addr(renderer.mlx_texture.handle, &renderer.mlx_texture.bpp, &renderer.mlx_texture.size_line, &renderer.mlx_texture.endian);
	if (renderer.mlx_texture.data == NULL)
	{
		printf("MLX IMG CAN'T GET IMG DATA BUFFER ADDRESS.");
		return 1;
	}
	renderer.scene.camera = new_camera((t_vec3){0, -3, 0}, (t_vec3){0, 1, 0}, (float)renderer.win_height / renderer.win_width, 180);
	print_camera_value(renderer.scene.camera);
	renderer.scene.objects_count = 1;
	renderer.scene.objects = new_sphere((t_vec3){0, 0, 0}, 1.0f, (t_vec3){255.0f, 0, 0});
	print_object_value(renderer.scene.objects);

	mlx_key_hook(renderer.window,key_hook,&renderer);
	mlx_loop_hook(renderer.mlx_context, render, &renderer);
	mlx_loop(renderer.mlx_context);
	return 0;
}