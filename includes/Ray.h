/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:15:22 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:15:33 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
#define RAY_H
#include "Mat4x4.h"
#include "Camera.h"

typedef struct s_object t_object;

typedef struct s_hit
{
	int is_valid;
	t_vec3 normal;
	t_vec4 uv_map;
	t_object *object;
	t_vec3 hit_point;
	t_vec3 color;
	float distance;
} t_hit;


typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 target;
	t_vec3 dir;
} t_ray;

t_ray	get_ray(t_camera*camera, t_vec3 pixel, t_vec3 img_size);

#endif // RAY_H