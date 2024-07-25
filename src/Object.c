#include "Object.h"

t_vec3 get_object_pos(t_mat4x4 *SRT_matrix)
{
    t_vec3 pos;

    pos.x = *mat_at(SRT_matrix, 0, 3);
    pos.y = *mat_at(SRT_matrix, 1, 3);
    pos.z = *mat_at(SRT_matrix, 2, 3);

    return pos;
}
void set_object_pos(t_mat4x4 *SRT_matrix, t_vec3 pos)
{
    *mat_at(SRT_matrix, 0, 3) = pos.x;
    *mat_at(SRT_matrix, 1, 3) = pos.y;
    *mat_at(SRT_matrix, 2, 3) = pos.z;
}