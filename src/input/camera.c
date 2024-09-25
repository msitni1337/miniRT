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

void	control_camera_1(int key, t_camera *cam, t_mat4x4 rot)
{
	if (key == KEY_UP)
	{
		rot = get_x_rotation_matrix(10);
		cam->forward = mat_mul_vec3(&rot, &cam->forward);
	}
	else if (key == KEY_DOWN)
	{
		rot = get_x_rotation_matrix(-10);
		cam->forward = mat_mul_vec3(&rot, &cam->forward);
		cam->forward = vec3_normalize(cam->forward);
	}
	else if (key == KEY_LEFT)
	{
		rot = get_z_rotation_matrix(10);
		cam->forward = mat_mul_vec3(&rot, &cam->forward);
		cam->forward = vec3_normalize(cam->forward);
	}
	else if (key == KEY_RIGHT)
	{
		rot = get_z_rotation_matrix(-10);
		cam->forward = mat_mul_vec3(&rot, &cam->forward);
		cam->forward = vec3_normalize(cam->forward);
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
		control_camera_1(key, cam, (t_mat4x4){0});
	calculate_camera_uv(cam);
}
