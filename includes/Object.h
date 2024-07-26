#ifndef OBJECT_H
#define OBJECT_H
#include "Ray.h"

typedef enum e_object_type
{
	OBJ_PLANE,
	OBJ_SPHERE,
	OBJ_LIGHT,
	OBJ_CONE,
} t_object_type;

typedef struct s_object
{
	t_object_type type;
	struct s_hit (*intersection)(struct s_object *object, struct s_ray ray);
	t_mat4x4 SRT_matrix;
	t_mat4x4 ISRT_matrix;
	t_vec3 color;
	float object_data;
} t_object;

typedef struct s_scene
{
	t_camera camera;
	size_t objects_count;
	t_object *objects;
} t_scene;

t_mat4x4 get_euler_rotation_matrix(t_vec3 normalized_orientation);

t_object new_light(t_vec3 pos, float intensity, t_vec3 color);
t_object new_sphere(t_vec3 pos, float radius, t_vec3 color);
void set_object_pos(t_object *object, t_vec3 pos);
t_vec3 get_object_pos(t_object *object);
t_object *get_next_object_by_type(t_scene *scene, size_t *i, t_object_type type);

#endif //SPHERE_H