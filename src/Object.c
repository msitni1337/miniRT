#include "Object.h"

t_object *get_next_object_by_type(t_scene *scene, size_t *i, t_object_type type)
{
    while(scene->objects && *i < scene->objects_count)
    {
        if (scene->objects[*i].type == type)
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