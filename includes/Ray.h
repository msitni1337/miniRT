#ifndef RAY_H
#define RAY_H
#include "Mat4x4.h"
#include "Camera.h"

typedef struct s_hit
{
	int is_valid;
	t_vec3 normal;
	void *object;
	t_vec3 hit_point;
	t_vec3 color;
	float data;
} t_hit;


typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 target;
	t_vec3 dir;
} t_ray;

t_ray	get_ray(t_camera*camera, t_vec3 pixel, t_vec3 img_size);
t_ray	apply_mat(t_ray ray, t_mat4x4 mat);

#endif // RAY_H