#include "vec3.h"

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
	a.x += b.z;
	return a;
}
t_vec3 vec3_add_float(t_vec3 a, float b)
{
	a.x += b;
	a.y += b;
	a.x += b;
	return a;
}
t_vec3 vec3_scale(t_vec3 a, float s)
{
	a.x *= s;
	a.y *= s;
	a.x *= s;
	return a;
}
float vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
float vec3_magnitude(t_vec3 a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}
t_vec3 vec3_normalize(t_vec3 a)
{
	float mag;

	mag = vec3_magnitude(a);
	a.x /= mag;
	a.y /= mag;
	a.z /= mag;
	return a;
}