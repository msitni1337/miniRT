/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mat4x4.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:14:58 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:15:33 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4X4_H
#define MAT4X4_H
#define MAT_COLS 4
#define MAT_ROWS 4
#include "Vec3.h"

typedef struct s_mat3x3
{
	float data[(MAT_ROWS - 1) * (MAT_COLS - 1)];
} t_mat3x3;

typedef struct s_mat4x4
{
	float data[MAT_ROWS * MAT_COLS];
} t_mat4x4;

t_mat4x4 mat_id();
t_mat4x4 mat_inv(t_mat4x4 *m1);
t_mat3x3 mat_sub_mat(t_mat4x4 *m1, int x, int y);
float mat4_determinant(t_mat4x4 *m1);
float mat3_determinant(t_mat3x3 *m1);
t_mat4x4 mat4_transpose(t_mat4x4*m1);
t_mat4x4 mat_mul(t_mat4x4 *m1, t_mat4x4 *m2);
t_vec3 mat_mul_vec3(t_mat4x4 *mat, t_vec3 *vec);
float *mat_at(t_mat4x4* mat, unsigned int row, unsigned int col);

void mat_print(float *data,int rows);
#endif // MAT4X4_H