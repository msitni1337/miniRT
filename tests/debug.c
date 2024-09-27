/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:18:23 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:18:24 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer.h"
#include <stdio.h>

void mat_print(float *data,int rows)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		printf("| ");
		while (j < rows)
		{
			printf("%5.2f ", data[(i * rows) + j]);
			j++;
		}
		printf("|\n");
		i++;
	}
}
void print_vec3(t_vec3 u)
{
	printf("| %7.4f  |\n", u.x);
	printf("| %7.4f  |\n", u.y);
	printf("| %7.4f  |\n", u.z);
}
void print_vec4(t_vec4 u)
{
	printf("| %7.4f  |\n", u.x);
	printf("| %7.4f  |\n", u.y);
	printf("| %7.4f  |\n", u.z);
	printf("| %7.4f  |\n", u.w);
}
void print_camera_value(t_camera camera)
{
	printf("camera.origin: \n");
	print_vec3(camera.origin);
	printf("camera.forward: \n");
	print_vec3(camera.forward);
	printf("camera.U: \n");
	print_vec3(camera.U);
	printf("camera.V: \n");
	print_vec3(camera.V);
	printf("camera.aspect_ratio: %f\n", camera.aspect_ratio);
}
void print_object_value(t_object object)
{
	printf("object.color: \n");
	print_vec3(object.color);
	printf("object.radius: %f\n", object.radius);
	printf("object.intensity: %f\n", object.intensity);
}