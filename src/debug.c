#include "Renderer.h"
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
	printf("| %7.4f  |\n", u.x);
	printf("| %7.4f  |\n", u.y);
	printf("| %7.4f  |\n", u.z);
}
void print_vec4(t_vec4 u)
{
	printf("| %7.4f  |\n", u.x);
	printf("| %7.4f  |\n", u.y);
	printf("| %7.4f  |\n", u.z);
	printf("| %7.4f  |\n", u.w);
}
void print_camera_value(t_camera camera)
{
	printf("camera.origin: \n");
	print_vec3(camera.origin);
	printf("camera.forward: \n");
	print_vec3(camera.forward);
	printf("camera.U: \n");
	print_vec3(camera.U);
	printf("camera.V: \n");
	print_vec3(camera.V);
	printf("camera.aspect_ratio: %f\n", camera.aspect_ratio);
}
void print_object_value(t_object object)
{
	printf("object.SRT_matrix: \n");
	mat_print(object.SRT_matrix.data, 4);
	printf("object.ISRT_matrix: \n");
	mat_print(object.ISRT_matrix.data, 4);
	printf("object.color: \n");
	print_vec3(object.color);
	printf("object.object_data: %f\n", object.object_data);
}