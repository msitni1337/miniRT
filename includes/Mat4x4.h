#ifndef MAT4X4_H
#define MAT4X4_H
#include "vec3.h"
#define MAT_COLS 4
#define MAT_ROWS 4

typedef struct s_mat4x4
{
	float data[MAT_ROWS * MAT_COLS];
} t_mat4x4;

t_mat4x4 mat_new(float val);
t_mat4x4 mat_id(); // { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0}
t_mat4x4 mat_inv(t_mat4x4 *m1);
t_mat4x4 mat_mul(t_mat4x4 *m1, t_mat4x4 *m2);
t_mat4x4 mat_mul_vec4(t_mat4x4 mat, t_vec4 vec);
t_mat4x4 vec4_mul_mat(t_vec4* vec, t_mat4x4* mat);
float *mat_at(t_mat4x4* mat, unsigned int row, unsigned int col);
void mat_print(t_mat4x4* mat);
#endif // MAT4X4_H