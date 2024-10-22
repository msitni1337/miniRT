/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:08 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:16:12 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vec3.h"

t_vec3 vec3_f(float x, float y, float z)
{
	t_vec3 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}
t_vec3 vec3_i(int x, int y, int z)
{
	t_vec3 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}
t_vec3 vec3_add_vec3(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return a;
}
t_vec3 vec3_sub_vec3(t_vec3 a, t_vec3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return a;
}
t_vec3 vec3_add_float(t_vec3 a, float b)
{
	a.x += b;
	a.y += b;
	a.z += b;
	return a;
}
t_vec3 vec3_cap(t_vec3 a, float min, float max)
{
	if (a.x < min)
		a.x = min;
	else if (a.x > max)
		a.x = max;
	if (a.y < min)
		a.y = min;
	else if (a.y > max)
		a.y = max;
	if (a.z < min)
		a.z = min;
	else if (a.z > max)
		a.z = max;
	return a;
}
t_vec3 vec3_mul(t_vec3 a, t_vec3 b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return a;
}
t_vec3 vec3_scale(t_vec3 a, float s)
{
	a.x *= s;
	a.y *= s;
	a.z *= s;
	return a;
}
t_vec3 vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);

	return result;
}
float vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
float vec3_magnitude(t_vec3 a)
{
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}
t_vec3 vec3_normalize(t_vec3 a)
{
	float mag;

	mag = vec3_magnitude(a);
	if (mag <= ZERO)
		return (t_vec3){0, 0, 0};
	a.x /= mag;
	a.y /= mag;
	a.z /= mag;
	return a;
}
t_vec4 vec3_to_vec4(t_vec3 a, float w)
{
	t_vec4 res;

	res.x = a.x;
	res.y = a.y;
	res.z = a.z;
	res.w = w;
	return res;
}
t_vec3 vec4_to_vec3(t_vec4 a)
{
	t_vec3 res;

	res.x = a.x;
	res.y = a.y;
	res.z = a.z;
	return res;
}
float float_cap(float val, float min, float max)
{
	if (val < min)
		return min;
	if (val > max)
		return max;
	return val;
}
int int_cap(int val, int min, int max)
{
	if (val < min)
		return min;
	if (val > max)
		return max;
	return val;
}