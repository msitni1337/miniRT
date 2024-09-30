/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:05:18 by msitni            #+#    #+#             */
/*   Updated: 2024/09/25 09:05:19 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	control_camera_1(int key, t_camera *cam)
{
	if (key == KEY_UP)
	{
		rotate_axis(cam->U, &cam->forward, &cam->V, 5);
	}
	else if (key == KEY_DOWN)
	{
		rotate_axis(cam->U, &cam->forward, &cam->V, -5);
	}
	else if (key == KEY_LEFT)
	{
		rotate_axis(cam->V, &cam->forward, &cam->U, -5);
	}
	else if (key == KEY_RIGHT)
	{
		rotate_axis(cam->V, &cam->forward, &cam->U, 5);
	}
}

void	control_camera(int key, t_camera *cam)
{
	if (key == KEY_W)
		cam->origin = vec3_add_vec3(cam->origin, vec3_scale(cam->forward,
					SENS));
	else if (key == KEY_S)
		cam->origin = vec3_add_vec3(cam->origin, vec3_scale(cam->forward,
					-SENS));
	else if (key == KEY_A)
		cam->origin = vec3_add_vec3(cam->origin, vec3_scale(cam->U, -SENS));
	else if (key == KEY_D)
		cam->origin = vec3_add_vec3(cam->origin, vec3_scale(cam->U, SENS));
	else if (key == KEY_8)
		cam->origin.z += SENS;
	else if (key == KEY_2)
		cam->origin.z -= SENS;
	else
		control_camera_1(key, cam);
	calculate_camera_uv(cam);
}
