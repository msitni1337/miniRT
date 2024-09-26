/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:59:03 by msitni            #+#    #+#             */
/*   Updated: 2024/09/26 03:05:19 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	create_canvas(t_renderer *r)
{
	r->mlx_texture.width = r->win_width;
	r->mlx_texture.height = r->win_height;
	r->mlx_texture.handle = mlx_new_image(r->mlx_context, r->mlx_texture.width,
			r->mlx_texture.height);
	if (r->mlx_texture.handle == NULL)
	{
		free_textures_filenames(&r->scene);
		ft_free(r->scene.objects, r->scene.lights, NULL);
		log_error("MLX IMG INIT FAILED.");
		return (1);
	}
	r->mlx_texture.data = mlx_get_data_addr(r->mlx_texture.handle,
			&r->mlx_texture.bpp, &r->mlx_texture.size_line,
			&r->mlx_texture.endian);
	if (r->mlx_texture.data == NULL)
	{
		mlx_destroy_image(r->mlx_context, r->mlx_texture.handle);
		free_textures_filenames(&r->scene);
		ft_free(r->scene.objects, r->scene.lights, NULL);
		log_error("MLX IMG CAN'T GET IMG DATA BUFFER ADDRESS.");
		return (1);
	}
	return (0);
}

int	init_mlx(t_renderer *r)
{
	r->mlx_context = mlx_init();
	if (r->mlx_context == NULL)
	{
		free_textures_filenames(&r->scene);
		ft_free(r->scene.objects, r->scene.lights, NULL);
		log_error("MLX INIT FAILED.");
		return (1);
	}
	r->win_width = WIN_WIDTH;
	r->win_height = WIN_HEIGHT;
	r->window = mlx_new_window(r->mlx_context, r->win_width, r->win_height,
			WIN_TITLE);
	if (r->window == NULL)
	{
		free_textures_filenames(&r->scene);
#ifndef INPUT_MAC
		mlx_destroy_display(r->mlx_context);
#endif
		ft_free(r->scene.objects, r->scene.lights, r->mlx_context);
		log_error("MLX WINDOW INIT FAILED.");
		return (1);
	}
	return (0);
}

void	free_all(t_renderer *r)
{
	free_objects_textures(r->mlx_context, r->scene.objects,
		r->scene.objects_count);
	ft_free(r->scene.objects, r->scene.lights, NULL);
	mlx_destroy_image(r->mlx_context, r->mlx_texture.handle);
	mlx_destroy_window(r->mlx_context, r->window);
#ifndef INPUT_MAC
	mlx_destroy_display(r->mlx_context);
#endif
	free(r->mlx_context);
}

int	start_mlx(t_renderer *r)
{
	if (init_mlx(r))
		return (1);
	if (create_canvas(r))
	{
		mlx_destroy_window(r->mlx_context, r->window);
#ifndef INPUT_MAC
		mlx_destroy_display(r->mlx_context);
#endif
		free(r->mlx_context);
		return (1);
	}
	if (set_objects_textures(r->mlx_context, &r->scene))
	{
		free_textures_filenames(&r->scene);
		free_all(r);
		return (1);
	}
	hook_input(r);
	mlx_loop(r->mlx_context);
	return (0);
}
