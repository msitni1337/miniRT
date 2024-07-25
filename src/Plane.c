#include "Object.h"

t_hit plane_intersection(t_object *object, t_ray ray)
{
    /*
        Handle plane intersection.
    */
    return (t_hit){0};
}

t_object new_plane(t_vec3 point, t_vec3 normal, t_vec3 color)
{
    t_object plane;

    plane.type = OBJ_PLANE;
    plane.color = vec3_scale(color, 1.0f / 255.0f);
    plane.intersection = &plane_intersection;
    plane.SRT_matrix = mat_id();
    set_object_pos(&plane, point);
    plane.ISRT_matrix = mat_inv(&plane.SRT_matrix);
    return plane;
}