/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Basic_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:18:17 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:18:24 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mat4x4.h"
#include "Renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_arrays.h"
#include "parser.h"
#include "input.h"

int main(int c, char **v)
{
	srand(0);
	t_renderer renderer;

	renderer.mlx_context = mlx_init();
	if (renderer.mlx_context == NULL)
	{
		log_error("MLX INIT FAILED.");
		return 1;
	}
	renderer.win_width = WIN_WIDTH;
	renderer.win_height = WIN_HEIGHT;
	renderer.window = mlx_new_window(renderer.mlx_context, renderer.win_width, renderer.win_height, WIN_TITLE);
	if (renderer.window == NULL)
	{
		log_error("MLX WINDOW INIT FAILED.");
		return 1;
	}
	renderer.mlx_texture.width = renderer.win_width;
	renderer.mlx_texture.height = renderer.win_height;
	renderer.mlx_texture.handle = mlx_new_image(renderer.mlx_context, renderer.mlx_texture.width, renderer.mlx_texture.height);
	if (renderer.mlx_texture.handle == NULL)
	{
		log_error("MLX IMG INIT FAILED.");
		return 1;
	}
	renderer.mlx_texture.data = mlx_get_data_addr(renderer.mlx_texture.handle, &renderer.mlx_texture.bpp, &renderer.mlx_texture.size_line, &renderer.mlx_texture.endian);
	if (renderer.mlx_texture.data == NULL)
	{
		log_error("MLX IMG CAN'T GET IMG DATA BUFFER ADDRESS.");
		return 1;
	}
	renderer.scene.ambient_color = vec3_scale((t_vec3){1.0f, 1.0f, 1.0f}, 0.7f);

	t_darr objects = init_da(sizeof(t_object));
	t_object obj;
	t_darr lights = init_da(sizeof(t_light));
	t_light light;

	/*  Scene 01:
	 */
	renderer.scene.camera = new_camera((t_vec3){0, -40, 5}, (t_vec3){0, 1, 0}, (float)renderer.win_height / renderer.win_width, 180);
	obj = new_plane((t_vec3){0, 0, -5}, (t_vec3){0, 0, 1}, (t_vec3){100.0f, 50.0f, 255.0f});
	obj.checkerboard = TRUE;
	add_to_arr(&objects, &obj);
	obj = new_rect((t_vec3){15, 15, 5}, (t_vec3){-1, -1, 0}, (t_vec3){255.0f, 255.0f, 255.0f}, (t_vec3){40, 20, 0});
	obj.checkerboard = TRUE;
	obj.reflection = .7;
	add_to_arr(&objects, &obj);
	obj = new_rect((t_vec3){-15, 15, 5}, (t_vec3){1, -1, 0}, (t_vec3){255.0f, 255.0f, 255.0f}, (t_vec3){40, 20, 0});
	obj.reflection = .7;
	add_to_arr(&objects, &obj);

	obj = new_sphere((t_vec3){0, 0, 3}, 5, (t_vec3){255.0f, 255.0f, 255.0f});
	if (set_texture(renderer.mlx_context, &obj.texture, "planet.xpm") == NULL)
	{
		log_error("MLX IMG CAN'T SET OBJ TEXTURE.");
		return 1;
	}
	if (set_texture(renderer.mlx_context, &obj.normal_map, "planet_normal.xpm") == NULL)
	{
		log_error("MLX IMG CAN'T SET OBJ TEXTURE.");
		return 1;
	}
	add_to_arr(&objects, &obj);

	light = new_light((t_vec3){-10, 0, 8}, 1.0f, (t_vec3){255.0f, 0.0f, 0.0f});
	add_to_arr(&lights, &light);
	light = new_light((t_vec3){10, 0, 8}, 1.0f, (t_vec3){0.0f, 255.0f, 0.0f});
	add_to_arr(&lights, &light);
	light = new_light((t_vec3){0, -10, 0}, 1.0f, (t_vec3){0.0f, 0.0f, 255.0f});
	add_to_arr(&lights, &light);

	/*	Pool Table:
		renderer.scene.camera = new_camera((t_vec3){0, -30, 20}, (t_vec3){0, 1, -.7}, (float)renderer.win_height / renderer.win_width, 120);
		obj = new_plane((t_vec3){0, 0, 0}, (t_vec3){0, 0, 1}, (t_vec3){255.0f, 255.0f, 255.0f});
		obj.checkerboard = 1;
		add_to_arr(&objects, &obj);
		obj = new_rect((t_vec3){0, 0, 5}, (t_vec3){0, 0, 1}, (t_vec3){0.0f, 255.0f, 0.0f}, (t_vec3){30, 10, 0});
		obj.reflection = 0.6f;
		add_to_arr(&objects, &obj);

		obj = new_rect((t_vec3){0, 5, 5.25}, (t_vec3){0, -1, 0}, (t_vec3){0.0f, 255.0f, 0.0f}, (t_vec3){30, .5, 0});
		add_to_arr(&objects, &obj);

		obj = new_rect((t_vec3){0, -5, 5.25}, (t_vec3){0, -1, 0}, (t_vec3){0.0f, 255.0f, 0.0f}, (t_vec3){30, .5, 0});
		add_to_arr(&objects, &obj);

		obj = new_rect((t_vec3){15, 0, 5.25}, (t_vec3){-1, 0, 0}, (t_vec3){0.0f, 255.0f, 0.0f}, (t_vec3){10, .5, 0});
		add_to_arr(&objects, &obj);

		obj = new_rect((t_vec3){-15, 0, 5.25}, (t_vec3){1, 0, 0}, (t_vec3){0.0f, 255.0f, 0.0f}, (t_vec3){10, .5, 0});
		add_to_arr(&objects, &obj);

		obj = new_rect((t_vec3){0, 0, 5}, (t_vec3){0, 0, 1}, (t_vec3){0.0f, 255.0f, 0.0f}, (t_vec3){30, 10, 0});
		add_to_arr(&objects, &obj);

		obj = new_rect((t_vec3){0, 0, 5}, (t_vec3){0, 0, 1}, (t_vec3){0.0f, 255.0f, 0.0f}, (t_vec3){30, 10, 0});
		add_to_arr(&objects, &obj);
		obj = new_cylinder((t_vec3){0.0f, 0, 1.0f}, (t_vec3){14.7, -4.7, 2.5}, (t_vec3){5, 0.5f, 0}, (t_vec3){250.0f, 150.0f, 150.0f});
		add_to_arr(&objects, &obj);
		obj.position.x = -obj.position.x;
		add_to_arr(&objects, &obj);
		obj.position.y = -obj.position.y;
		add_to_arr(&objects, &obj);
		obj.position.x = -obj.position.x;
		add_to_arr(&objects, &obj);
		obj = new_sphere((t_vec3){0, 0, 5.3}, .3, (t_vec3){255.0f, 0.0f, 255.0f});
		add_to_arr(&objects, &obj);
		obj.position.x = 2;
		obj.position.y = 5;
		add_to_arr(&objects, &obj);
		obj.position.y = -3;
		obj.color = (t_vec3){70.0f, 180.0f, 0.0f};
		add_to_arr(&objects, &obj);
		obj = new_sphere((t_vec3){10, 4.5, 5.3}, .3, (t_vec3){255.0f, 0.0f, 255.0f});
		add_to_arr(&objects, &obj);
		obj = new_sphere((t_vec3){-13, -1.5, 5.3}, .3, (t_vec3){10.0f, 10.0f, 10.0f});
		add_to_arr(&objects, &obj);
	*/

	// light = new_light((t_vec3){-80, 0, 50}, .7f, (t_vec3){0.0f, 255.0f, 0.0f});
	// add_to_arr(&lights, &light);

	renderer.scene.objects = objects.data;
	renderer.scene.objects_count = objects.count;

	renderer.scene.lights = lights.data;
	renderer.scene.lights_count = lights.count;

	renderer.tab_mode = FALSE;
	renderer.redraw = TRUE;
	renderer.selected_obj = NULL;

	mlx_hook(renderer.window, ON_KEYDOWN, 1L << 0, key_hook_down, &renderer);
	mlx_hook(renderer.window, ON_KEYUP, 1L << 1, key_hook_up, &renderer);
	mlx_loop_hook(renderer.mlx_context, render, &renderer);
	mlx_hook(renderer.window, ON_MOUSEDOWN, 1L << 2, mouse_hook_down, &renderer);
	mlx_hook(renderer.window, ON_MOUSEUP, 1L << 3, mouse_hook_up, &renderer);
	mlx_loop(renderer.mlx_context);
	return 0;
}