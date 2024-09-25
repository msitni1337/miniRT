/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:05:23 by msitni            #+#    #+#             */
/*   Updated: 2024/09/25 09:05:24 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	control_selected_obj_2(int key, t_object *obj)
{
	t_mat4x4	rot;

	if (key == KEY_RIGHT)
	{
		rot = get_y_rotation_matrix(-10);
		obj->normal = mat_mul_vec3(&rot, &obj->normal);
		obj->normal = vec3_normalize(obj->normal);
	}
	else if (key == KEY_4)
	{
		rot = get_z_rotation_matrix(5);
		obj->normal = mat_mul_vec3(&rot, &obj->normal);
		obj->normal = vec3_normalize(obj->normal);
	}
	else if (key == KEY_6)
	{
		rot = get_z_rotation_matrix(-5);
		obj->normal = mat_mul_vec3(&rot, &obj->normal);
		obj->normal = vec3_normalize(obj->normal);
	}
}

void	control_selected_obj_1(int key, t_object *obj)
{
	t_mat4x4	rot;

	if (key == KEY_UP)
	{
		rot = get_x_rotation_matrix(10);
		obj->normal = mat_mul_vec3(&rot, &obj->normal);
		obj->normal = vec3_normalize(obj->normal);
	}
	else if (key == KEY_DOWN)
	{
		rot = get_x_rotation_matrix(-10);
		obj->normal = mat_mul_vec3(&rot, &obj->normal);
		obj->normal = vec3_normalize(obj->normal);
	}
	else if (key == KEY_LEFT)
	{
		rot = get_y_rotation_matrix(10);
		obj->normal = mat_mul_vec3(&rot, &obj->normal);
		obj->normal = vec3_normalize(obj->normal);
	}
	else
		control_selected_obj_2(key, obj);
}

void	control_selected_obj(int key, t_object *obj)
{
	if (key == KEY_A)
		obj->position.x -= SENS;
	else if (key == KEY_D)
		obj->position.x += SENS;
	else if (key == KEY_S)
		obj->position.y -= SENS;
	else if (key == KEY_W)
		obj->position.y += SENS;
	else if (key == KEY_8)
		obj->position.z += SENS;
	else if (key == KEY_2)
		obj->position.z -= SENS;
	else
		control_selected_obj_1(key, obj);
	obj->recalculate(obj);
}
