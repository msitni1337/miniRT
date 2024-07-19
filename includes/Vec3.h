#ifndef VEC3_H
#define VEC3_H
#include <math.h>
#include <assert.h>

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
t_vec3 vec3_scale(t_vec3 a, float s);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
float vec3_dot(t_vec3 a, t_vec3 b);

t_vec3 vec3_normalize(t_vec3 a);
float vec3_magnitude(t_vec3 a);
t_vec4 vec3_to_vec4(t_vec3 a, float w);
t_vec3 vec4_to_vec3(t_vec4 a);
void print_vec3(t_vec3 u);
void print_vec4(t_vec4 u);

#endif // VEC3_H