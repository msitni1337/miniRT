#ifndef VEC3_H
#define VEC3_H
#include <math.h>

typedef struct s_vec3
{
	float x;
	float y;
	float z;
} t_vec3;

t_vec3 vec3_f(float x, float y, float z);
t_vec3 vec3_i(int x, int y, int z);
t_vec3 vec3_add_vec3(t_vec3 a, t_vec3 b);
t_vec3 vec3_add_float(t_vec3 a, float b);
t_vec3 vec3_scale(t_vec3 a, float s);
float vec3_dot(t_vec3 a, t_vec3 b);

t_vec3 vec3_normalize(t_vec3 a);
float vec3_magnitude(t_vec3 a);

#endif // VEC3_H