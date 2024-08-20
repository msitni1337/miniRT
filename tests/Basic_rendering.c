#include "Mat4x4.h"
#include "Renderer.h"
#include <stdio.h>
#include <stdlib.h>

int key_hook(int key, t_renderer *renderer)
{
	printf("key pressed: %d\n", key);
	switch (key)
	{
	case KEY_UP:
		renderer->scene.camera.forward.y += 0.5f;
		renderer->redraw = TRUE;
		break;
	case KEY_DOWN:
		renderer->scene.camera.forward.y -= 0.5f;
		renderer->redraw = TRUE;
		break;
	case KEY_LEFT:
		renderer->scene.camera.forward.x -= 0.5f;
		renderer->redraw = TRUE;
		break;
	case KEY_RIGHT:
		renderer->scene.camera.forward.x += 0.5f;
		renderer->redraw = TRUE;
		break;
	case KEY_Z:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale(renderer->scene.camera.forward, 0.5f));
		renderer->redraw = TRUE;
		break;
	case KEY_S:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale(renderer->scene.camera.forward, -0.5f));
		renderer->redraw = TRUE;
		break;
	case KEY_Q:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale(renderer->scene.camera.U, -0.5f));
		renderer->redraw = TRUE;
		break;
	case KEY_D:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale(renderer->scene.camera.U, 0.5f));
		renderer->redraw = TRUE;
		break;
	case KEY_8:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale((t_vec3){0, 0, 1.0}, 0.5f));
		renderer->redraw = TRUE;
		break;
	case KEY_2:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale((t_vec3){0, 0, 1.0}, -0.5f));
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale(renderer->scene.camera.forward, -0.5f));
		renderer->redraw = TRUE;
		break;
	default:
		break;
	}
	calculate_camera_uv(&renderer->scene.camera);
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
	renderer.scene.camera = new_camera((t_vec3){0, -10, 0}, (t_vec3){0, 1, 0}, (float)renderer.win_height / renderer.win_width, 180);

	renderer.scene.objects_count = 4;
	t_object objects[renderer.scene.objects_count];
	renderer.scene.objects = objects;
	renderer.scene.objects[0] = new_sphere((t_vec3){-1, 0, 0}, 1.0f, (t_vec3){255.0f, 0, 0});
	renderer.scene.objects[1] = new_cylinder((t_vec3){0, 0, 1}, (t_vec3){1, 0, 0}, (t_vec3){1, 1, 0}, (t_vec3){255.0f, 25.0f, 70.0f});
	renderer.scene.objects[2] = new_plane((t_vec3){0, 0, -1}, (t_vec3){0.0, 0.0, 1.0}, (t_vec3){30.0f, 80.0f, 45.0f});
	renderer.scene.objects[3] = new_light((t_vec3){1, -4, 2}, 1.0f, (t_vec3){255.0f, 255.0f, 255.0f});
	renderer.redraw = TRUE;

	print_camera_value(renderer.scene.camera);
	print_object_value(renderer.scene.objects[0]);
	print_object_value(renderer.scene.objects[1]);

	mlx_key_hook(renderer.window, key_hook, &renderer);
	mlx_loop_hook(renderer.mlx_context, render, &renderer);
	mlx_loop(renderer.mlx_context);
	return 0;
}