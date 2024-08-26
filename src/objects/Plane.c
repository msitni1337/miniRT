#include "Object.h"

t_vec3 plane_point_normal(t_hit hit_point)
{
    return ((t_object *)hit_point.object)->normal;
}

t_vec3 plane_map_uvs(t_hit hit_point)
{
    t_object *obj;
    t_vec3 tmp;

    obj = hit_point.object;
    tmp = vec3_sub_vec3(obj->uvs_origin, hit_point.hit_point);

    return (t_vec3){vec3_dot(tmp, obj->u_vector), vec3_dot(tmp, obj->v_vector), 0.0f};
}

t_hit plane_intersection(t_object *object, t_ray ray)
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

    // t_vec3 map_origine = mat_mul_vec3(&object->ISRT_matrix, &ray.origin);
    // t_vec3 map_target = mat_mul_vec3(&object->ISRT_matrix, &ray.target);
    // t_vec3 map_direct = vec3_sub_vec3(map_target, map_origine);
    // map_direct = vec3_normalize(map_direct);

    float dot_na = vec3_dot(object->normal, ray.origin);
    float dot_nd = vec3_dot(object->normal, ray.dir);
    float dot_np = vec3_dot(object->normal, get_object_pos(object));

    t_hit hit;
    hit.object = NULL;
    hit.data = INF;
    if (fabs(dot_nd) > ZERO)
    {
        float t = (dot_np - dot_na) / dot_nd;
        if (t <= CAM_CLIP)
            return hit;
        hit.object = object;
        hit.hit_point = vec3_scale(ray.dir, t);
        hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
        hit.data = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));
        hit.normal = plane_point_normal(hit);
    }
    return hit;
}

void plane_calculate_uvs(t_object*plane)
{
    t_vec3 tmp;
    float sqrt3;

    sqrt3 = sqrtf(3);
    plane->u_vector = vec3_sub_vec3((t_vec3){0,0,0}, get_object_pos(plane));
    tmp = vec3_sub_vec3((t_vec3){sqrt3,sqrt3,sqrt3}, get_object_pos(plane));

    plane->u_vector = vec3_mul(plane->normal, plane->u_vector);
    plane->u_vector = vec3_mul(plane->normal, tmp);
    
    plane->u_vector = vec3_normalize(vec3_sub_vec3(tmp, plane->u_vector));
    plane->v_vector = vec3_cross(plane->normal, plane->u_vector);

   
    plane->uvs_origin = vec3_add_vec3(vec3_scale(plane->u_vector, 10000.0f), vec3_scale(plane->v_vector, 10000.0f));
}

t_object new_plane(t_vec3 point, t_vec3 normal, t_vec3 color)
{
    t_object plane;

    plane.type = OBJ_PLANE;
    plane.color = vec3_scale(color, 1.0f / 255.0f);
    plane.intersection = &plane_intersection;
    plane.map_uvs = &plane_map_uvs;
    plane.calculate_uvs = &plane_calculate_uvs;
    plane.normal = vec3_normalize(normal);
    
    plane.SRT_matrix = mat_id();
    set_object_pos(&plane, point);
    plane.ISRT_matrix = mat_inv(&plane.SRT_matrix);

    plane_calculate_uvs(&plane);
    plane.bump_map.handle = NULL;
    // plane.point_normal = &plane_point_normal;


    // tmp = get_euler_rotation_matrix(normal);
    // plane.SRT_matrix = mat_mul(&tmp, &plane.SRT_matrix);

    return plane;
}