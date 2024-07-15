#include "Mat4x4.h"
#include <stdio.h>

void mat_print(t_mat4x4 *mat)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (i < MAT_ROWS)
	{
		j = 0;
		printf("| ");
		while (j < MAT_COLS)
		{
			printf("%.2f ", *mat_at(mat, i, j));
			j++;
		}
		printf("|\n");
		i++;
	}
}