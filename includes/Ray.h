#ifndef RAY_H
#define RAY_H
#include "Vec3.h"
#include "Camera.h"
#include "Scene.h"

typedef struct s_hit
{
	t_vec3	hit_point;
	float	distance;
} t_hit;


typedef struct s_ray
{
	t_vec3 point;
	t_vec3 dir;
} t_ray;

t_ray	get_ray(t_camera*camera, t_vec3 pixel);
t_hit*	cast_ray(t_scene*scene, t_ray ray);
#endif // RAY_H