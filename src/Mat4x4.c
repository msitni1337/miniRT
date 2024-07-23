#include "Mat4x4.h"

t_mat4x4 mat_new(float val)
{
	assert(!"NOT IMPLEMENTED"); // TODO: Possibly not needed
	return (t_mat4x4){0};
}
t_mat4x4 mat_inv(t_mat4x4 *m1)
{
	assert(!"NOT IMPLEMENTED");
	return (t_mat4x4){0};
}
t_mat4x4 mat_mul(t_mat4x4 *m1, t_mat4x4 *m2)
{
	t_mat4x4 res;
	int row;
	int col;
	int i;

	res = (t_mat4x4){0};
	row = 0;
	while (row < MAT_ROWS)
	{
		col = 0;
		while (col < MAT_COLS)
		{
			i = 0;
			while (i < MAT_COLS)
			{
				*mat_at(&res, row, col) += *mat_at(m1, row, i) * *mat_at(m2, i, col); 
				i++;
			}
			col++;
		}
		row++;
	}
	return res;
}
t_vec3 mat_mul_vec3(t_mat4x4* mat, t_vec3 *vec)
{
	assert(!"NOT IMPLEMENTED");
	return (t_vec3){0};
}
float *mat_at(t_mat4x4 *mat, unsigned int row, unsigned int col)
{
	return &(mat->data[(row * MAT_COLS) + col]);
}
t_mat4x4 mat_id()
{
	t_mat4x4 id;
	unsigned int i;
	unsigned int j;

	i = 0;
	while (i < MAT_ROWS)
	{
		j = 0;
		while (j < MAT_COLS)
		{
			if (i == j)
				*mat_at(&id, i, j) = 1.0f;
			else
				*mat_at(&id, i, j) = 0.0f;
			j++;
		}
		i++;
	}
	return id;
}