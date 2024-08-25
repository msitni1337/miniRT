#include "Mat4x4.h"
#include "Renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_arrays.h"

int key_hook(int key, t_renderer *renderer)
{
	printf("key pressed: %d\n", key);
	switch (key)
	{
	case KEY_UP:
	{
		t_mat4x4 x_rot = get_x_rotation_matrix(10);
		renderer->scene.camera.forward = mat_mul_vec3(&x_rot, &renderer->scene.camera.forward);
		renderer->redraw = TRUE;
		break;
	}
	case KEY_DOWN:
	{
		t_mat4x4 x_rot = get_x_rotation_matrix(-10);
		renderer->scene.camera.forward = mat_mul_vec3(&x_rot, &renderer->scene.camera.forward);
		renderer->redraw = TRUE;
		break;
	}
	case KEY_LEFT:
	{
		t_mat4x4 x_rot = get_z_rotation_matrix(10);
		renderer->scene.camera.forward = mat_mul_vec3(&x_rot, &renderer->scene.camera.forward);
		renderer->redraw = TRUE;
		break;
	}
	case KEY_RIGHT:
	{
		t_mat4x4 x_rot = get_z_rotation_matrix(-10);
		renderer->scene.camera.forward = mat_mul_vec3(&x_rot, &renderer->scene.camera.forward);
		renderer->redraw = TRUE;
		break;
	}
	case KEY_W:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale(renderer->scene.camera.forward, 2.0f));
		renderer->redraw = TRUE;
		break;
	case KEY_S:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale(renderer->scene.camera.forward, -2.0f));
		renderer->redraw = TRUE;
		break;
	case KEY_A:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale(renderer->scene.camera.U, -2.0f));
		renderer->redraw = TRUE;
		break;
	case KEY_D:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale(renderer->scene.camera.U, 2.0f));
		renderer->redraw = TRUE;
		break;
	case KEY_8:
		renderer->scene.camera.origin.z += 2.0f;
		renderer->redraw = TRUE;
		break;
	case KEY_2:
		renderer->scene.camera.origin.z -= 2.0f;
		renderer->redraw = TRUE;
		break;
	case KEY_4:
	{
		t_mat4x4 x_rot = get_x_rotation_matrix(1);
		renderer->scene.objects[renderer->scene.objects_count - 1].normal = mat_mul_vec3(&x_rot, &renderer->scene.objects[renderer->scene.objects_count - 1].normal);
		renderer->redraw = TRUE;
		break;
	}
	case KEY_6:
	{
		t_mat4x4 x_rot = get_x_rotation_matrix(-1);
		renderer->scene.objects[renderer->scene.objects_count - 1].normal = mat_mul_vec3(&x_rot, &renderer->scene.objects[renderer->scene.objects_count - 1].normal);
		renderer->redraw = TRUE;
		break;
	}
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
	renderer.scene.camera = new_camera((t_vec3){0, -20, 2}, (t_vec3){0, 1, 0}, (float)renderer.win_height / renderer.win_width, 70);
	renderer.scene.ambient_color = (t_vec3){1.0f, 1.0f, 1.0f};
	renderer.scene.ambient_intemsity = 0.5f;

	t_darr objects = init_da(sizeof(t_object));
	t_object obj;

	obj = new_plane((t_vec3){0, 0, -1}, (t_vec3){0.0, 0.0, 1.0}, (t_vec3){130.0f, 20.0f, 200.0f});
	add_to_arr(&objects, &obj);

	obj = new_plane((t_vec3){0, 10, 0}, (t_vec3){0.0, -1.0, 0.0}, (t_vec3){10.0f, 50.0f, 100.0f});
	add_to_arr(&objects, &obj);

	obj = new_sphere((t_vec3){-6, -2, 0}, 4.0f, (t_vec3){255.0f, 0, 0});
	add_to_arr(&objects, &obj);

	obj = new_sphere((t_vec3){0, 0, 0}, .5f, (t_vec3){255.0f, 0, 0});
	add_to_arr(&objects, &obj);

	obj = new_cylinder((t_vec3){0.0f, 0.0, 1.0f}, (t_vec3){2, -7, 0}, (t_vec3){2, 2, 0}, (t_vec3){10.0f, 125.0f, 70.0f});
	add_to_arr(&objects, &obj);

	obj = new_cylinder((t_vec3){0.0f, 0, 1.0f}, (t_vec3){5, -3, 2}, (t_vec3){6, .5f, 0}, (t_vec3){10.0f, 125.0f, 70.0f});
	add_to_arr(&objects, &obj);

	obj = new_cone((t_vec3){0.0f, 0, 1.0f}, (t_vec3){0, -7, 2}, (t_vec3){1, 5, 0}, (t_vec3){10.0f, 125.0f, 70.0f});
	add_to_arr(&objects, &obj);

	obj = new_light((t_vec3){-1, -2, 10}, 1.0f, (t_vec3){255.0f, 255.0f, 255.0f});
	add_to_arr(&objects, &obj);
	/*
		obj = new_light((t_vec3){4, -2, 8.2f}, 1.0f, (t_vec3){255.0f, 255.0f, 255.0f});
		add_to_arr(&objects, &obj);
	*/

	obj = new_rect((t_vec3){5, 2, 2}, (t_vec3){0.0, -1.0, -.2}, (t_vec3){200.0f, 80.0f, 145.0f}, (t_vec3){6.0, 4.0, 0.0});
	add_to_arr(&objects, &obj);

	renderer.scene.objects = objects.data;
	renderer.scene.objects_count = objects.count;
	for (size_t i = 0; i < renderer.scene.objects_count; i++)
	{
		renderer.scene.objects[i].reflection = 0;
		renderer.scene.objects[i].checkerboard = 0;
	}

	renderer.scene.objects[objects.count - 1].reflection = .5;
	// renderer.scene.objects[objects.count - 1].checkerboard = 1;

	renderer.redraw = TRUE;

	print_camera_value(renderer.scene.camera);

	mlx_key_hook(renderer.window, key_hook, &renderer);
	mlx_loop_hook(renderer.mlx_context, render, &renderer);
	mlx_loop(renderer.mlx_context);
	return 0;
}