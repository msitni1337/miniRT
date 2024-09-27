/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:15:01 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:15:33 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
#define MLX_UTILS_H
#include <mlx.h>

typedef struct s_img
{
	char*filename;
	void *handle;
	char *data;
	int bpp;
	int size_line;
	int width;
	int height;
	int endian;
} t_img;

void set_img_pixel_at(t_img *img, int x, int y, int color);
unsigned int get_img_pixel_at(t_img*img, int x, int y);

#endif // MLX_UTILS_H