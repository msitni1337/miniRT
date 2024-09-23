#include "Object.h"

// t_object *get_next_object_by_type(t_scene *scene, size_t *i, t_object_type type)
// {
//     while (scene->objects.data && *i < scene->objects.count)
//     {
//         if (scene->objects.data[*i].type & type)
//             return &scene->objects.data[*i];
//         (*i)++;
//     }
//     return NULL;
// }

/*
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
*/

t_vec3 get_axis_rotation(t_vec3 normalized_orientation, t_vec3 axis)
{
    float cos_theta;
    float sin_theta;

    cos_theta = vec3_dot(axis, normalized_orientation);
    sin_theta = sqrtf(1 - cos_theta * cos_theta);

    return vec3_f(cos_theta, sin_theta, 0);
}

t_mat4x4 get_x_rotation_matrix(float angle)
{
    t_mat4x4 x_rot;

    float cos = cosf((angle / 180) * PI);
    float sin = sinf((angle / 180) * PI);

    x_rot = mat_id();
    *mat_at(&x_rot, 1, 1) = cos;
    *mat_at(&x_rot, 1, 2) = -sin;
    *mat_at(&x_rot, 2, 1) = sin;
    *mat_at(&x_rot, 2, 2) = cos;

    return x_rot;
}

t_mat4x4 get_y_rotation_matrix(float angle)
{
    t_mat4x4 y_rot;

    float cos = cosf((angle / 180) * PI);
    float sin = sinf((angle / 180) * PI);

    y_rot = mat_id();
    *mat_at(&y_rot, 0, 0) = cos;
    *mat_at(&y_rot, 0, 2) = sin;
    *mat_at(&y_rot, 2, 0) = -sin;
    *mat_at(&y_rot, 2, 2) = cos;

    return y_rot;
}

t_mat4x4 get_z_rotation_matrix(float angle)
{
    t_mat4x4 z_rot;

    float cos = cosf((angle / 180) * PI);
    float sin = sinf((angle / 180) * PI);

    z_rot = mat_id();
    *mat_at(&z_rot, 0, 0) = cos;
    *mat_at(&z_rot, 0, 1) = -sin;
    *mat_at(&z_rot, 1, 0) = sin;
    *mat_at(&z_rot, 1, 1) = cos;
    return z_rot;
}

t_hit cap_intersection(t_vec3 cap_normal, t_vec3 cap_center, float radius, t_ray ray)
{
    float dot_na = vec3_dot(cap_normal, ray.origin);
    float dot_nd = vec3_dot(cap_normal, ray.dir);
    float dot_np = vec3_dot(cap_normal, cap_center);

    t_hit hit;
    hit.is_valid = FALSE;
    if (fabs(dot_nd) > ZERO)
    {
        float t = (dot_np - dot_na) / dot_nd;
        if (t <= CAM_CLIP)
            return hit;
        hit.hit_point = vec3_scale(ray.dir, t);
        hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
        hit.distance = vec3_magnitude(vec3_sub_vec3(hit.hit_point, ray.origin));
        if (vec3_magnitude(vec3_sub_vec3(hit.hit_point, cap_center)) <= radius)
            hit.is_valid = TRUE;
    }
    return hit;
}

t_vec4 cap_map_uv(t_vec3 vec, t_vec3 u, t_vec3 v, float radius)
{
    t_vec4 uv_map;

    uv_map.z = vec3_dot(vec, u);
    uv_map.w = vec3_dot(vec, v);
    uv_map.x = (uv_map.z / radius) * 0.5f + 0.5f;
    uv_map.y = (uv_map.w / radius) * 0.5f + 0.5f;
    return uv_map;
}