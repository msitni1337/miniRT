#include "Mat4x4.h"
#include <stdio.h>

void mat_print(float *data,int rows)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		printf("| ");
		while (j < rows)
		{
			printf("%5.2f ", data[(i * rows) + j]);
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