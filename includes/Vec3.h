/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:15:30 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:15:33 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
#define VEC3_H
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "logging.h"
#define TRUE 1
#define FALSE 0
#define ERROR	1
#define SUCESS	0
#define ZERO 1e-30
#define PI 3.14159265358979323846264
#define CAM_CLIP 0.1f
#define INF 1e8f
#define FLT_MAX 3.402823466e+38F
#define FLT_MIN 1.175494351e-38F

typedef struct s_vec3
{
	float x;
	float y;
	float z;
} t_vec3;

typedef struct s_vec4
{
	float x;
	float y;
	float z;
	float w;
} t_vec4;

t_vec3 vec3_f(float x, float y, float z);
t_vec3 vec3_i(int x, int y, int z);
t_vec3 vec3_add_vec3(t_vec3 a, t_vec3 b);
t_vec3 vec3_add_float(t_vec3 a, float b);
t_vec3 vec3_sub_vec3(t_vec3 a, t_vec3 b);
t_vec3 vec3_scale(t_vec3 a, float s);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
float vec3_dot(t_vec3 a, t_vec3 b);

t_vec3 vec3_normalize(t_vec3 a);
float vec3_magnitude(t_vec3 a);
t_vec4 vec3_to_vec4(t_vec3 a, float w);
t_vec3 vec4_to_vec3(t_vec4 a);

int int_cap(int val, int min, int max);
float float_cap(float val, float min, float max);
t_vec3 vec3_cap(t_vec3 a, float min, float max);
t_vec3 vec3_mul(t_vec3 a, t_vec3 b);

#endif // VEC3_H