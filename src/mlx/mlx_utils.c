/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:16:05 by msitni            #+#    #+#             */
/*   Updated: 2024/09/26 02:58:37 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer.h"
#include "input.h"

void	set_img_pixel_at(t_img *img, int x, int y, int color)
{
	char	*tmp;

	tmp = &(img->data[x * (img->bpp / 8) + y * img->size_line]);
	*(unsigned int *)tmp = color;
}

unsigned int	get_img_pixel_at(t_img *img, int x, int y)
{
	char	*tmp;

	tmp = &(img->data[x * (img->bpp / 8) + y * img->size_line]);
	return (*(unsigned int *)tmp);
}

void	hook_input(t_renderer *r)
{
	r->tab_mode = FALSE;
	r->redraw = TRUE;
	r->selected_obj = NULL;
	mlx_hook(r->window, ON_KEYDOWN, 1L << 0, key_hook_down, r);
	mlx_hook(r->window, ON_KEYUP, 1L << 1, key_hook_up, r);
	mlx_loop_hook(r->mlx_context, render, r);
	mlx_hook(r->window, ON_MOUSEDOWN, 1L << 2, mouse_hook_down, r);
	mlx_hook(r->window, ON_MOUSEUP, 1L << 3, mouse_hook_up, r);
	mlx_hook(r->window, ON_DESTROY, 0L, on_destroy, r);
}
