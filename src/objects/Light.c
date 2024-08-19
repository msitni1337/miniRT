#include "Object.h"

t_hit light_intersection(t_object *object, t_ray ray)
{
    /*
        Handle light intersection with other objects.. shadows
    */
    return (t_hit){0};
}

t_object new_light(t_vec3 pos, float intensity, t_vec3 color)
{
    t_object light;

    light.type = OBJ_LIGHT;
    light.color = vec3_scale(color, 1.0f / 255.0f);
    light.intersection = &light_intersection;
    light.intensity = float_cap(intensity, 0.0f, 1.0f);
    light.SRT_matrix = mat_id();
    set_object_pos(&light, pos);
    light.ISRT_matrix = mat_inv(&light.SRT_matrix);
    return light;
}