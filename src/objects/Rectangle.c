#include "Object.h"

<<<<<<< HEAD
=======
t_vec3 rect_point_normal(t_hit hit_point)
{
    /*
    return ((t_object *)hit_point.object)->normal;
    */
   return (t_vec3){0};
}

>>>>>>> 9443dd4 (not yet)
t_hit rect_intersection(t_object *object, t_ray ray)
{
    /*
        p => point of plane
        n => Normal
        a + t d

        nx(x - px) + ny(y - py) + nz(z - pz) = 0

        nx((ax + t dx) - px) + ny((ay + t dy) - py) + nz((az + t dz) - pz) = 0

        nx * ax + t * nx * dx + ny * ay + t * ny * dy + nz * az + t * nz * dz - nx*px - ny*py - nz*pz= 0

        (nx*ax + ny*ay + nz*az) + t (nx * dx + ny * dy + nz * dz) - (nx*px + ny*py + nz*pz)

        dot(n, a) + t dot(n, d) - dot(n, p) = 0
        t = (dot(n, p) - dot(n , a)) / dot(n , d))
    */
<<<<<<< HEAD
    t_hit hit;
    hit.object = object;
    hit.is_valid = FALSE;

=======

    // t_vec3 map_origine = mat_mul_vec3(&object->ISRT_matrix, &ray.origin);
    // t_vec3 map_target = mat_mul_vec3(&object->ISRT_matrix, &ray.target);
    // t_vec3 map_direct = vec3_sub_vec3(map_target, map_origine);
    // map_direct = vec3_normalize(map_direct);
/*
>>>>>>> 9443dd4 (not yet)
    float dot_na = vec3_dot(object->normal, ray.origin);
    float dot_nd = vec3_dot(object->normal, ray.dir);
    float dot_np = vec3_dot(object->normal, object->position);

    if (fabs(dot_nd) > ZERO)
    {
        float t = (dot_np - dot_na) / dot_nd;
        if (t > CAM_CLIP)
        {
            hit.hit_point = vec3_scale(ray.dir, t);
            hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
            hit.distance = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));
            hit.normal = object->normal;

            t_vec3 point_vec = vec3_sub_vec3(hit.hit_point, object->position);
            float x_dis = vec3_dot(object->orth_normal, point_vec);
            float y_dis = vec3_dot(object->orth_normal2, point_vec);

            if (fabs(x_dis) <= object->width / 2 && fabs(y_dis) <= object->height / 2)
            {
                hit.is_valid = TRUE;
                hit.uv_map = (t_vec4){x_dis / (object->width / 2), y_dis / (object->height / 2), x_dis, y_dis};
            }
        }
    }
    return hit;
*/

   return (t_hit){0};

}

void rect_recalculate(t_object *obj)
{
    obj->anti_normal = vec3_scale(obj->normal, -1);

    obj->orth_normal = vec3_normalize(vec3_cross(obj->normal, (t_vec3){0.0f, 0.0f, 1.0f}));
    if (vec3_magnitude(obj->orth_normal) <= ZERO)
        obj->orth_normal = vec3_normalize(vec3_cross(obj->normal, (t_vec3){0.0f, 1.0f, 0.0f}));

    obj->orth_normal2 = vec3_cross(obj->normal, obj->orth_normal);
}

t_object new_rect(t_vec3 centre_point, t_vec3 normal, t_vec3 color, t_vec3 dimensions)
{
    t_object rect;
    t_mat4x4 tmp;

    rect = (t_object){0};
    rect.type = OBJ_RECT;
    rect.intersection = &rect_intersection;
<<<<<<< HEAD
    rect.recalculate = &rect_recalculate;
    rect.position = centre_point;
    rect.normal = vec3_normalize(normal);
    rect.height = dimensions.y;
    rect.width = dimensions.x;
    rect.color = vec3_scale(color, 1.0f / 255.0f);
    rect_recalculate(&rect);
=======
    // rect.uvs_origin = centre_point;

    rect.height = dimensions.y;
    rect.width = dimensions.x;
    // rect.point_normal = &rect_point_normal;

    rect.normal = vec3_normalize(normal);

    //rect.SRT_matrix = mat_id();
    // tmp = get_euler_rotation_matrix(normal);
    // rect.SRT_matrix = mat_mul(&tmp, &rect.SRT_matrix);
    //set_object_pos(&rect, centre_point);
    // rect.ISRT_matrix = mat_inv(&rect.SRT_matrix);

>>>>>>> 9443dd4 (not yet)
    return rect;
}