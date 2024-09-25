/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:16:05 by msitni            #+#    #+#             */
/*   Updated: 2024/09/25 10:16:05 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer.h"

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
