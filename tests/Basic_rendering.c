#include "Mat4x4.h"
#include "Renderer.h"
#include <stdio.h>
#include <stdlib.h>

int key_hook(int key, t_renderer *renderer)
{
	printf("key pressed: %d\n",key);
	switch (key)
	{
	case KEY_UP:
		renderer->scene.camera.origin.y += 0.1f;
		renderer->redraw = TRUE;
		break;
	case KEY_DOWN:
		renderer->scene.camera.origin.y -= 0.1f;
		renderer->redraw = TRUE;
		break;
	case KEY_LEFT:
		renderer->scene.camera.origin.x -= 0.1f;
		renderer->redraw = TRUE;
		break;
	case KEY_RIGHT:
		renderer->scene.camera.origin.x += 0.1f;
		renderer->redraw = TRUE;
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
		LOG_ERROR("MLX INIT FAILED.");
		return 1;
	}
	renderer.win_width = 1280;
	renderer.win_height = 720;
	renderer.window = mlx_new_window(renderer.mlx_context, renderer.win_width, renderer.win_height, WIN_TITLE);
	if (renderer.window == NULL)
	{
		LOG_ERROR("MLX WINDOW INIT FAILED.");
		return 1;
	}
	renderer.mlx_texture.width = renderer.win_width;
	renderer.mlx_texture.height = renderer.win_height;
	renderer.mlx_texture.handle = mlx_new_image(renderer.mlx_context, renderer.mlx_texture.width, renderer.mlx_texture.height);
	if (renderer.mlx_texture.handle == NULL)
	{
		LOG_ERROR("MLX IMG INIT FAILED.");
		return 1;
	}
	renderer.mlx_texture.data = mlx_get_data_addr(renderer.mlx_texture.handle, &renderer.mlx_texture.bpp, &renderer.mlx_texture.size_line, &renderer.mlx_texture.endian);
	if (renderer.mlx_texture.data == NULL)
	{
		LOG_ERROR("MLX IMG CAN'T GET IMG DATA BUFFER ADDRESS.");
		return 1;
	}
	renderer.scene.camera = new_camera((t_vec3){0, -10, 0}, (t_vec3){0, 1, 0}, (float)renderer.win_height / renderer.win_width, 120);
	
	renderer.scene.objects_count = 4;
	renderer.scene.objects = malloc(sizeof(t_object) * renderer.scene.objects_count);
	if (renderer.scene.objects == NULL)
	{
		LOG_ERROR("MALLOC FAILED.");
		return 1;
	}
	renderer.scene.objects[0] = new_sphere((t_vec3){0, 0, 0}, 1.0f, (t_vec3){255.0f, 0, 0});
	renderer.scene.objects[1] = new_sphere((t_vec3){4, 0, 0}, 1.0f, (t_vec3){0, 255.0f, 0});
	renderer.scene.objects[2] = new_sphere((t_vec3){-4, 0, 0}, 1.0f, (t_vec3){0, 0, 255.0f});
	renderer.scene.objects[3] = new_light((t_vec3){0, 0, 20}, 1.0f, (t_vec3){255.0f, 255.0f, 255.0f});
	renderer.redraw = TRUE;

	print_camera_value(renderer.scene.camera);
	print_object_value(renderer.scene.objects[0]);
	print_object_value(renderer.scene.objects[1]);

	mlx_key_hook(renderer.window,key_hook,&renderer);
	mlx_loop_hook(renderer.mlx_context, render, &renderer);
	mlx_loop(renderer.mlx_context);
	return 0;
}