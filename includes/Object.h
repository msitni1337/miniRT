/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:15:12 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:15:33 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
#define OBJECT_H
#include "Ray.h"
#include "mlx_utils.h"

typedef enum e_object_type
{
	OBJ_PLANE    = (1 << 1),
	OBJ_SPHERE   = (1 << 2),
	OBJ_CYLINDER = (1 << 3),
	OBJ_CONE     = (1 << 4),
	OBJ_RECT     = (1 << 5),
} t_object_type;

typedef struct s_object
{
	t_object_type type;
	struct s_hit (*intersection)(struct s_object *object, struct s_ray ray);
	// t_vec3 (*map_uvs)(t_hit hit_point);
	void (*recalculate)(struct s_object* obj);
	//struct s_vec3 (*point_normal)(t_hit hit_point);
	// t_mat4x4 SRT_matrix;
	// t_mat4x4 ISRT_matrix;
	t_vec3 normal;
	t_vec3 anti_normal;
	t_vec3 orth_normal;
	t_vec3 orth_normal2;

	t_vec3 top_cap_center;
	t_vec3 bottom_cap_center;

	t_img texture;
	t_img normal_map;
	t_vec3 cone_tip;

	
	t_vec3 color;
	t_vec3 position;
	float reflection;
	float height;
	float width;
	float radius;
	float intensity;
	int checkerboard;
	int hidden;
} t_object;

typedef struct s_light
{
	t_vec3 position;
	t_vec3 color;
	float intensity;
} t_light;

typedef struct s_scene
{
	t_camera camera;
	size_t objects_count;
	t_object *objects;
	size_t lights_count;
	t_light *lights;
	t_vec3 ambient_color;
} t_scene;

typedef struct s_quad_eq
{
	float a;
	float b;
	float c;
	float det;
	float t;
} t_quad_eq;

t_light new_light(t_vec3 position, float intensity, t_vec3 color);
t_object new_sphere(t_vec3 pos, float radius, t_vec3 color);
t_object new_plane(t_vec3 point, t_vec3 normal, t_vec3 color);
t_object new_cylinder(t_vec3 normal, t_vec3 center, t_vec3 height_diameter, t_vec3 color);
t_object new_cone_cap(t_vec3 normal, t_vec3 center, t_vec3 height_diameter, t_vec3 color);
t_object new_cone(t_vec3 normal, t_vec3 center, t_vec3 height_diameter, t_vec3 color);
t_object new_rect(t_vec3 centre_point, t_vec3 normal, t_vec3 color, t_vec3 dimensions);

t_mat4x4 get_x_rotation_matrix(float angle);
t_mat4x4 get_y_rotation_matrix(float angle);
t_mat4x4 get_z_rotation_matrix(float angle);
// t_vec3 get_object_pos(t_object *object);
t_object *get_next_object_by_type(t_scene *scene, size_t *i, t_object_type type);


void solve_quad_eq(t_quad_eq eq, t_hit*hit, t_ray ray);
t_hit cap_intersection(t_vec3 cap_normal, t_vec3 cap_center, float radius, t_ray ray);
t_vec4 cap_map_uv(t_vec3 vec, t_vec3 u, t_vec3 v, float radius);
t_vec4 cone_map_uv(t_hit hit, t_object *obj);
void cone_recalculate(t_object *obj);
t_hit cone_intersection(t_object *object, t_ray ray);
int set_objects_textures(void* mlx, t_scene* scene);
void free_textures_filenames(t_scene* scene);

// void set_object_pos(t_object *object, t_vec3 pos);
#endif // OBJECT_H