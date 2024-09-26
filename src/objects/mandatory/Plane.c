#include "Object.h"

void plane_map_uvs(t_hit *hit, t_object *obj)
{
    t_vec3 point_vec;
    float x_dis;
    float y_dis;

    point_vec = vec3_sub_vec3(hit->hit_point, obj->position);
    x_dis = vec3_dot(obj->orth_normal, point_vec);
    y_dis = vec3_dot(obj->orth_normal2, point_vec);
    hit->uv_map.x = x_dis / INF;
    hit->uv_map.x = hit->uv_map.x * 0.5f + 0.5f;
    hit->uv_map.y = y_dis / INF;
    hit->uv_map.y = hit->uv_map.y * 0.5f + 0.5f;
    hit->uv_map.z = x_dis;
    hit->uv_map.w = y_dis;
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
    t_hit hit;
    float dot_na; 
    float dot_nd; 
    float dot_np; 

    hit.object = object;
    hit.is_valid = FALSE;
    dot_na = vec3_dot(object->normal, ray.origin);
    dot_nd = vec3_dot(object->normal, ray.dir);
    dot_np = vec3_dot(object->normal, object->position);
    if (fabs(dot_nd) > ZERO)
    {
        float t = (dot_np - dot_na) / dot_nd;
        if (t > CAM_CLIP)
        {
            hit.is_valid = TRUE;
            hit.hit_point = vec3_scale(ray.dir, t);
            hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
            hit.distance = vec3_magnitude(vec3_sub_vec3(ray.origin, hit.hit_point));
            hit.normal = object->normal;
            plane_map_uvs(&hit, object);
        }
    }
    return hit;
}

void plane_recalculate(t_object *obj)
{
    obj->anti_normal = vec3_scale(obj->normal, -1);

    obj->orth_normal = vec3_normalize(vec3_cross(obj->normal, (t_vec3){0.0f, 0.0f, 1.0f}));
    if (vec3_magnitude(obj->orth_normal) <= ZERO)
        obj->orth_normal = vec3_normalize(vec3_cross(obj->normal, (t_vec3){0.0f, 1.0f, 0.0f}));

    obj->orth_normal2 = vec3_cross(obj->normal, obj->orth_normal);
}

t_object new_plane(t_vec3 point, t_vec3 normal, t_vec3 color)
{
    t_object plane;

    plane = (t_object){0};
    plane.type = OBJ_PLANE;
    plane.intersection = &plane_intersection;
    plane.recalculate = &plane_recalculate;
    plane.position = point;
    plane.normal = vec3_normalize(normal);
    plane.color = vec3_scale(color, 1.0f / 255.0f);
    plane_recalculate(&plane);
    return plane;
}