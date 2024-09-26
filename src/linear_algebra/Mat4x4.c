#include "Mat4x4.h"

t_mat3x3 mat_sub_mat(t_mat4x4 *m1, int x, int y)
{
	t_mat3x3 result;
	int i;
	int row;
	int col;

	i = 0;
	row = 0;
	while (row < MAT_ROWS)
	{
		col = 0;
		while (col < MAT_COLS)
		{
			if ((row != x) && (col != y))
			{
				result.data[i] = *mat_at(m1, row, col);
				i++;
			}
			col++;
		}
		row++;
	}
	return result;
}
t_mat4x4 mat_scale(t_mat4x4 *m1, float s)
{
	t_mat4x4 result;
	int i;

	i = 0;
	while (i < MAT_ROWS * MAT_COLS)
	{
		result.data[i] = m1->data[i] * s;
		i++;
	}
	return result;
}
t_mat4x4 mat4_transpose(t_mat4x4 *m1)
{
	t_mat4x4 result;
	int row;
	int col;

	row = 0;
	while (row < MAT_ROWS)
	{
		col = 0;
		while (col < MAT_COLS)
		{
			*mat_at(&result, row, col) = *mat_at(m1, col, row);
			col++;
		}
		row++;
	}

	return result;
}
float mat3_determinant(t_mat3x3 *m1)
{
	float *m;
	float det;
	int col;
	/*
		| a b c |
		| d e f | => det = aei + bfg + cdh - ceg -bdi-afh
		| g h i |

		or :

			det = m1.00 * (m1.11 * m1.22 - m1.21 * m1.12)
			det += m1.10 * (m1.01 * m1.22 - m1.21 * m1.02)
			det += m1.20 * (m1.01 * m1.12 - m1.11 * m1.02)
	*/
	m = m1->data;
	det = m[0] * m[(1 * 3) + 1] * m[(2 * 3) + 2];
	det += m[1] * m[(1 * 3) + 2] * m[(2 * 3) + 0];
	det += m[2] * m[(1 * 3) + 0] * m[(2 * 3) + 1];
	det -= m[2] * m[(1 * 3) + 1] * m[(2 * 3) + 0];
	det -= m[1] * m[(1 * 3) + 0] * m[(2 * 3) + 2];
	det -= m[0] * m[(1 * 3) + 2] * m[(2 * 3) + 1];

	return det;
}
float mat4_determinant(t_mat4x4 *m1)
{
	float det;
	int sign;
	int col;

	det = 0;
	sign = 1;
	col = 0;
	while (col < MAT_COLS)
	{
		t_mat3x3 sub_mat = mat_sub_mat(m1, 0, col);
		float sub_mat_det = mat3_determinant(&sub_mat);
		det += sign * *mat_at(m1, 0, col) * sub_mat_det;
		sign *= -1;
		col++;
	}
	return det;
}
t_mat4x4 mat_inv(t_mat4x4 *m1)
{
	t_mat4x4 adjugate;

	int sign = 1;
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			t_mat3x3 sub_mat = mat_sub_mat(m1, row, col);
			float sub_mat_det = mat3_determinant(&sub_mat);
			*mat_at(&adjugate, row, col) = sign * sub_mat_det;
			sign *= -1;
		}
		sign *= -1;
	}
	adjugate = mat4_transpose(&adjugate);
	float determinant = mat4_determinant(m1);
	if (fabs(determinant) <= ZERO)
		return (t_mat4x4){0};
	return mat_scale(&adjugate, 1.0f / determinant);
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
t_vec3 mat_mul_vec3(t_mat4x4 *mat, t_vec3 *vec)
{
	t_vec4 result;
	float sum;
	int row;

	result = vec3_to_vec4(*vec, 1.0f);
	row = 0;
	while (row < MAT_ROWS)
	{
		sum = 0;

		sum += mat->data[row * MAT_COLS + 0] * result.x;
		sum += mat->data[row * MAT_COLS + 1] * result.y;
		sum += mat->data[row * MAT_COLS + 2] * result.z;
		sum += mat->data[row * MAT_COLS + 3] * result.w;

		*((float*)&result + row) = sum;
		row++;
	}
	return vec4_to_vec3(result);
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