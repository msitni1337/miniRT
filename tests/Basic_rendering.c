#include "Mat4x4.h"
#include "Renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_arrays.h"
#include "input.h"

void *set_bump_map(void *mlx_ptr, t_object *obj, char *filename)
{
	obj->bump_map.handle = mlx_xpm_file_to_image(mlx_ptr, filename, obj->bump_map.width, obj->bump_map.height);
	if (obj->bump_map.handle == NULL)
		return NULL;
	obj->bump_map.data = mlx_get_data_addr(obj->bump_map.handle, &obj->bump_map.bpp, &obj->bump_map.size_line, &obj->bump_map.endian);
	return obj->bump_map.handle;
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
	renderer.scene.camera = new_camera((t_vec3){0, -30, 10}, (t_vec3){0, 1, -.3}, (float)renderer.win_height / renderer.win_width, 120);
	renderer.scene.ambient_color = (t_vec3){1.0f, 1.0f, 1.0f};
	renderer.scene.ambient_intensity = 0.5f;

	t_darr objects = init_da(sizeof(t_object));
	t_object obj;
	/*
	obj = new_cylinder((t_vec3){0.0f, 0, 1.0f}, (t_vec3){0, 50, 0}, (t_vec3){10, 100.5f, 0}, (t_vec3){250.0f, 150.0f, 150.0f});
	add_to_arr(&objects, &obj);
	*/
	obj = new_cone((t_vec3){0.0f, 0, 1.0f}, (t_vec3){0, -10, 0}, (t_vec3){14, 5.5f, 0}, (t_vec3){250.0f, 0.0f, 150.0f});
	add_to_arr(&objects, &obj);
	/*
	obj = new_sphere((t_vec3) {0, 0, 0}, 5, (t_vec3){255.0f, 255.0f, 255.0f});
	add_to_arr(&objects, &obj);
	*/

	t_darr lights = init_da(sizeof(t_light));
	t_light light;
	light = new_light((t_vec3){20, 0, 10}, .5f, (t_vec3){255.0f, 255.0f, 255.0f});
	add_to_arr(&lights, &light);
	light = new_light((t_vec3){-20, 0, 10}, .7f, (t_vec3){255.0f, 255.0f, 255.0f});
	add_to_arr(&lights, &light);

	renderer.scene.objects = objects.data;
	renderer.scene.objects_count = objects.count;

	renderer.scene.lights = lights.data;
	renderer.scene.lights_count = lights.count;

	for (size_t i = 0; i < renderer.scene.objects_count; i++)
	{
		renderer.scene.objects[i].reflection = 0;
		renderer.scene.objects[i].checkerboard = 0;
	}
	renderer.scene.objects[0].reflection = .7;
	renderer.scene.objects[0].checkerboard = 1;


	renderer.tab_mode = FALSE;
	renderer.redraw = TRUE;
	renderer.selected_obj = NULL;

	set_bump_map(renderer.mlx_context, &renderer.scene.objects[0], "");

	mlx_hook(renderer.window, ON_KEYDOWN, 1L << 0, key_hook_down, &renderer);
	mlx_hook(renderer.window, ON_KEYUP, 1L << 1, key_hook_up, &renderer);
	mlx_loop_hook(renderer.mlx_context, render, &renderer);
	mlx_hook(renderer.window, ON_MOUSEDOWN, 1L << 2, mouse_hook_down, &renderer);
	mlx_hook(renderer.window, ON_MOUSEUP, 1L << 3, mouse_hook_up, &renderer);
	mlx_loop(renderer.mlx_context);
	return 0;
}

/*
		obj = new_plane((t_vec3){0, 0, -1}, (t_vec3){0.0, 0.0, 1.0}, (t_vec3){130.0f, 20.0f, 200.0f});
		add_to_arr(&objects, &obj);

		obj = new_plane((t_vec3){0, 10, 0}, (t_vec3){0.0, -1.0, 0.0}, (t_vec3){10.0f, 50.0f, 100.0f});
		add_to_arr(&objects, &obj);

		obj = new_cone((t_vec3){0.0f, 0.0, 1.0f}, (t_vec3){0, 0, 0}, (t_vec3){2, 2, 0}, (t_vec3){150.0f, 25.0f, 170.0f});
		add_to_arr(&objects, &obj);


		obj = new_rect((t_vec3){5, 2, 2}, (t_vec3){0.0, -1.0, -.2}, (t_vec3){255.0f, 255.0f, 255.0f}, (t_vec3){6.0, 4.0, 0.0});
		add_to_arr(&objects, &obj);
	obj = new_plane((t_vec3){0, 0, -1}, (t_vec3){0.0, 0.0, 1.0}, (t_vec3){130.0f, 20.0f, 200.0f});
	add_to_arr(&objects, &obj);

	obj = new_plane((t_vec3){0, 10, 0}, (t_vec3){0.0, -1.0, 0.0}, (t_vec3){10.0f, 50.0f, 100.0f});
	add_to_arr(&objects, &obj);

	obj = new_sphere((t_vec3){-6, -2, 1}, 4.0f, (t_vec3){255.0f, 0, 0});
	add_to_arr(&objects, &obj);

	obj = new_sphere((t_vec3){0, 0, 0}, .05f, (t_vec3){255.0f, 0, 0});
	add_to_arr(&objects, &obj);

	obj = new_sphere((t_vec3){1, 0, 0}, .05f, (t_vec3){255.0f, 0, 0});
	add_to_arr(&objects, &obj);

	obj = new_sphere((t_vec3){0, 0, 1}, .05f, (t_vec3){255.0f, 0, 0});
	add_to_arr(&objects, &obj);

	obj = new_cylinder((t_vec3){0.0f, 0.0, 1.0f}, (t_vec3){2, -7, 0}, (t_vec3){2, 2, 0}, (t_vec3){10.0f, 125.0f, 70.0f});
	add_to_arr(&objects, &obj);

	obj = new_cylinder((t_vec3){0.0f, 0, 1.0f}, (t_vec3){5, -3, 2}, (t_vec3){6, .5f, 0}, (t_vec3){10.0f, 125.0f, 70.0f});
	add_to_arr(&objects, &obj);

	obj = new_cone((t_vec3){0.0f, 1.0, 0.0f}, (t_vec3){0, 0, 0}, (t_vec3){2, 2, 0}, (t_vec3){150.0f, 25.0f, 170.0f});
	add_to_arr(&objects, &obj);

	obj = new_light((t_vec3){-1, -2, 2}, .4f, (t_vec3){255.0f, 255.0f, 255.0f});
	add_to_arr(&objects, &obj);

	obj = new_light((t_vec3){2, -2, 4.0f}, 0.6f, (t_vec3){255.0f, 255.0f, 255.0f});
	add_to_arr(&objects, &obj);

	obj = new_rect((t_vec3){5, 2, 2}, (t_vec3){0.0, -1.0, -.2}, (t_vec3){255.0f, 255.0f, 255.0f}, (t_vec3){6.0, 4.0, 0.0});
	add_to_arr(&objects, &obj);
*/