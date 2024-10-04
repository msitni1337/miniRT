/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:15:27 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:15:33 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
#define DEBUG_H
#include "Renderer.h"
#include <stdio.h>

void mat_print(float *data,int rows);
void print_vec3(t_vec3 u);
void print_vec4(t_vec4 u);
void print_object_value(t_object object);
void print_camera_value(t_camera camera);
void print_mat(float *data,int rows);

#endif // DEBUG_H