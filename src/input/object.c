/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:05:23 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 07:07:03 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void control_selected_obj_4(int key, t_object *obj)
{
	if (key == KEY_PLUS_NUM && obj->radius < INF)
	{
		obj->radius += obj->radius * exp(-1);
		obj->radius = float_cap(obj->radius, ZERO, INF);
	}
	else if (key == KEY_MINUS_NUM && obj->radius > ZERO)
	{
		obj->radius -= obj->radius * exp(-1);
		obj->radius = float_cap(obj->radius, ZERO, INF);
	}
}

void control_selected_obj_3(int key, t_object *obj)
{
	if (key == KEY_PLUS && obj->height < INF)
	{
		obj->height += obj->height * exp(-1);
		obj->height = float_cap(obj->height, ZERO, INF);
	}
	else if (key == KEY_MINUS && obj->height > ZERO)
	{
		obj->height -= obj->height * exp(-1);
		obj->height = float_cap(obj->height, ZERO, INF);
	}
	else if (key == KEY_RPAREN && obj->width < INF)
	{
		obj->width += obj->width * exp(-1);
		obj->width = float_cap(obj->width, ZERO, INF);
	}
	else if (key == KEY_LPAREN && obj->width > ZERO)
	{
		obj->width -= obj->width * exp(-1);
		obj->width = float_cap(obj->width, ZERO, INF);
	}
	else
		control_selected_obj_4(key, obj);
}

void control_selected_obj_2(int key, t_object *obj)
{
	t_mat4x4 rot;

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
	else
		control_selected_obj_3(key, obj);
}

void control_selected_obj_1(int key, t_object *obj)
{
	t_mat4x4 rot;

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

void control_selected_obj(int key, t_object *obj)
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
	else if (key == KEY_H)
		obj->hidden = !obj->hidden;
	else
		control_selected_obj_1(key, obj);
	obj->recalculate(obj);
}
