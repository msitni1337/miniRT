#include "Object.h"

t_vec3 plane_point_normal(t_hit hit_point)
{
    return ((t_object*)hit_point.object)->normal;
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
        float t = (dot_np-dot_na) / dot_nd;
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


t_object new_plane(t_vec3 point, t_vec3 normal, t_vec3 color)
{
    t_object plane;
    t_mat4x4 tmp;

    plane.type = OBJ_PLANE;
    plane.color = vec3_scale(color, 1.0f / 255.0f);
    plane.intersection = &plane_intersection;
    plane.uvs_origin = point;
    //plane.point_normal = &plane_point_normal;
    
    
    plane.normal = vec3_normalize(normal);
    
    plane.SRT_matrix = mat_id();
    //tmp = get_euler_rotation_matrix(normal);
    //plane.SRT_matrix = mat_mul(&tmp, &plane.SRT_matrix);
    set_object_pos(&plane, point);
    plane.ISRT_matrix = mat_inv(&plane.SRT_matrix);
    
    return plane;
}