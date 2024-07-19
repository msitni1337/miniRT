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
			printf("%5.2f ", *mat_at(mat, i, j));
			j++;
		}
		printf("|\n");
		i++;
	}
}
void print_vec3(t_vec3 u)
{
	printf("| %5.2f |\n", u.x);
	printf("| %5.2f |\n", u.y);
	printf("| %5.2f |\n", u.z);
}
void print_vec4(t_vec4 u)
{
	printf("| %5.2f |\n", u.x);
	printf("| %5.2f |\n", u.y);
	printf("| %5.2f |\n", u.z);
	printf("| %5.2f |\n", u.w);
}