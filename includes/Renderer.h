/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:15:27 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:15:33 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
#define RENDERER_H
#include "Object.h"
#include "mlx_utils.h"

#define WIN_TITLE "miniRT"
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define BG_COLOR 0x00020515

typedef struct s_renderer
{
	t_object* selected_obj;
	void *mlx_context;
	void *window;
	int win_width;
	int win_height;
	t_img mlx_texture;
	t_scene scene;
	int redraw;
	int tab_mode;
} t_renderer;

t_hit cast_ray(t_scene *scene, t_ray ray, int hidden);
unsigned int get_color_vec3(t_vec3 vec);
t_vec3 get_vec3_color(unsigned int color);
t_vec3 shade_color(t_scene *scene, t_hit hit, t_ray ray);

int render(t_renderer *renderer);

// Debug
void print_camera_value(t_camera camera);
void print_object_value(t_object object);
int start_mlx(t_renderer *r);
void free_all(t_renderer* r);

#endif // RENDERER_H
