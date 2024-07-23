#ifndef RAY_H
#define RAY_H
#include "Mat4x4.h"
#include "Camera.h"
#include "Scene.h"

typedef struct s_hits
{
	size_t count;
	t_vec3*	hit_point;
	float*	distance;
} t_hits;


typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 target;
	t_vec3 dir;
} t_ray;

t_ray	get_ray(t_camera*camera, t_vec3 pixel, t_vec3 img_size);
t_ray	apply_mat(t_ray ray, t_mat4x4 mat);
t_hits	cast_ray(t_scene*scene, t_ray ray);

#endif // RAY_H