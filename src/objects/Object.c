#include "Object.h"

t_object *get_next_object_by_type(t_scene *scene, size_t *i, t_object_type type)
{
    while (scene->objects && *i < scene->objects_count)
    {
        if (scene->objects[*i].type & type)
            return &scene->objects[*i];
        (*i)++;
    }
    return NULL;
}
t_vec3 get_object_pos(t_object *object)
{
    t_vec3 pos;

    pos.x = *mat_at(&object->SRT_matrix, 0, 3);
    pos.y = *mat_at(&object->SRT_matrix, 1, 3);
    pos.z = *mat_at(&object->SRT_matrix, 2, 3);

    return pos;
}
void set_object_pos(t_object *object, t_vec3 pos)
{
    *mat_at(&object->SRT_matrix, 0, 3) = pos.x;
    *mat_at(&object->SRT_matrix, 1, 3) = pos.y;
    *mat_at(&object->SRT_matrix, 2, 3) = pos.z;
}

t_vec3 get_axis_rotation(t_vec3 normalized_orientation, t_vec3 axis)
{
    float cos_theta;
    float sin_theta;

    cos_theta = vec3_dot(axis, normalized_orientation);
    sin_theta = sqrtf(1 - cos_theta * cos_theta);

    return vec3_f(cos_theta, sin_theta, 0);
}

t_mat4x4 get_x_rotation_matrix(t_vec3 normalized_orientation)
{
    t_mat4x4 x_rot;
    t_vec3 theta;

    x_rot = mat_id();
    theta = get_axis_rotation(normalized_orientation, (t_vec3){0, 0, 1.0f});
    *mat_at(&x_rot, 1, 1) = theta.x;
    *mat_at(&x_rot, 1, 2) = -theta.y;
    *mat_at(&x_rot, 2, 1) = theta.y;
    *mat_at(&x_rot, 2, 2) = theta.x;
    
    return x_rot;
}

t_mat4x4 get_y_rotation_matrix(t_vec3 normalized_orientation)
{
    t_mat4x4 y_rot;
    t_vec3 theta;

    y_rot = mat_id();
    theta = get_axis_rotation(normalized_orientation, (t_vec3){1.0f, 0, 0});
    *mat_at(&y_rot, 0, 0) = theta.x;
    *mat_at(&y_rot, 0, 2) = theta.y;
    *mat_at(&y_rot, 2, 0) = -theta.y;
    *mat_at(&y_rot, 2, 2) = theta.x;
    
    return y_rot;
}

t_mat4x4 get_z_rotation_matrix(t_vec3 normalized_orientation)
{
    t_mat4x4 z_rot;
    t_vec3 theta;

    z_rot = mat_id();
    theta = get_axis_rotation(normalized_orientation, (t_vec3){0, 1.0f, 0});
    *mat_at(&z_rot, 0, 0) = theta.x;
    *mat_at(&z_rot, 0, 1) = -theta.y;
    *mat_at(&z_rot, 1, 0) = theta.y;
    *mat_at(&z_rot, 1, 1) = theta.x;
    return z_rot;
}

// Orientation should be normalized!
t_mat4x4 get_euler_rotation_matrix(t_vec3 normalized_orientation)
{
    t_mat4x4 x_rot;
    t_mat4x4 y_rot;
    t_mat4x4 z_rot;
    t_mat4x4 result;

    normalized_orientation = vec3_normalize(normalized_orientation);
    x_rot = get_x_rotation_matrix(normalized_orientation);
    y_rot = get_y_rotation_matrix(normalized_orientation);
    z_rot = get_z_rotation_matrix(normalized_orientation);

    result = mat_mul(&z_rot, &y_rot);
    result = mat_mul(&result, &x_rot);
    return result;
}