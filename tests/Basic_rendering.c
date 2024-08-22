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

	srand(0);
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
	renderer.scene.camera = new_camera((t_vec3){12, -12, 5}, (t_vec3){-1, 1, -.2f}, (float)renderer.win_height / renderer.win_width, 180);
	//renderer.scene.camera = new_camera((t_vec3){0, -20, 0}, (t_vec3){0, 1, 0}, (float)renderer.win_height / renderer.win_width, 180);
	renderer.scene.ambient_color = (t_vec3){1.0f, 1.0f, 1.0f};
	renderer.scene.ambient_intemsity = 0.4f;

	renderer.scene.objects_count = 8;
	t_object objects[renderer.scene.objects_count];
	renderer.scene.objects = objects;
	renderer.scene.objects[0] = new_plane((t_vec3){0, 10, 0}, (t_vec3){0.0, -1.0, 0.0}, (t_vec3){10.0f, 50.0f, 100.0f});
	renderer.scene.objects[1] = new_plane((t_vec3){0, 0, -1}, (t_vec3){0.0, 0.0, 1.0}, (t_vec3){130.0f, 80.0f, 145.0f});
	renderer.scene.objects[2] = new_sphere((t_vec3){-6, -2, 0}, 4.0f, (t_vec3){255.0f, 0, 0});
	renderer.scene.objects[3] = new_cylinder((t_vec3){0.0f, 0.0, 1.0f}, (t_vec3){2, -7, 0}, (t_vec3){2, 2, 0}, (t_vec3){10.0f, 125.0f, 70.0f});
	renderer.scene.objects[4] = new_cylinder((t_vec3){0.0f, 0, 1.0f}, (t_vec3){5, -1, 2}, (t_vec3){6, .5f, 0}, (t_vec3){10.0f, 125.0f, 70.0f});
	renderer.scene.objects[5] = new_light((t_vec3){5, -5, 5}, 1.0f, (t_vec3){255.0f, 255.0f, 255.0f});
	renderer.scene.objects[6] = new_light((t_vec3){-5, -3, 5}, .6f, (t_vec3){255.0f, 255.0f, 255.0f});
	renderer.scene.objects[7] = new_rect((t_vec3){0, 2, 5}, (t_vec3){0.0, -1.0, 0.0}, (t_vec3){200.0f, 80.0f, 145.0f} , (t_vec3){5.0, 2.0, 0.0});

	for (size_t i = 0; i < renderer.scene.objects_count; i++)
	{
		renderer.scene.objects[i].reflection = 0;
		renderer.scene.objects[i].checkerboard = 0;
	}
	renderer.scene.objects[2].reflection = .7f;
	//renderer.scene.objects[3].reflection = 1.0f;
	renderer.scene.objects[1].checkerboard = 0;
	renderer.redraw = TRUE;

	print_camera_value(renderer.scene.camera);

	mlx_key_hook(renderer.window, key_hook, &renderer);
	mlx_loop_hook(renderer.mlx_context, render, &renderer);
	mlx_loop(renderer.mlx_context);
	return 0;
}