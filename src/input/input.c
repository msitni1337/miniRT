/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:05:09 by msitni            #+#    #+#             */
/*   Updated: 2024/09/25 09:05:11 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	key_hook_up(int key, t_renderer *renderer)
{
	if (key == KEY_CTR)
		renderer->tab_mode = FALSE;
	return (0);
}

int	key_hook_down(int key, t_renderer *renderer)
{
	if (key == KEY_CTR)
		renderer->tab_mode = TRUE;
	else if (key == KEY_ESC)
		mlx_loop_end(renderer->mlx_context);
	else if (renderer->tab_mode)
	{
		control_camera(key, &renderer->scene.camera);
		renderer->redraw = TRUE;
	}
	else if (renderer->selected_obj)
	{
		control_selected_obj(key, renderer->selected_obj);
		renderer->redraw = TRUE;
	}
	return (0);
}

int	mouse_hook_up(int button, int x, int y, t_renderer *renderer)
{
	t_ray	ray;
	t_hit	hit;
	t_vec3	pixel;
	t_vec3	size;

	pixel.x = x;
	pixel.y = renderer->mlx_texture.height - y;
	size.x = renderer->mlx_texture.width;
	size.y = renderer->mlx_texture.height;
	ray = get_ray(&renderer->scene.camera, pixel, size);
	hit = get_ray_hit(&(renderer->scene), ray);
	if (hit.is_valid)
		renderer->selected_obj = hit.object;
	return (0);
}

int	mouse_hook_down(int button, int x, int y, t_renderer *renderer)
{
	(void)button;
	(void)x;
	(void)y;
	(void)renderer;
	return (0);
}

int	on_destroy(void *mlx)
{
	mlx_loop_end(mlx);
	return (0);
}
