#include "parser.h"

int main(int c, char **v)
{
	if (c != 3)
	{
		printf("args error\n");
		printf("%s [vec3] [float]\n", v[0]);
		return 1;
	}
	t_vec3 vec;
	if (get_vec3(&vec, v[1]))
	{
		printf("Error in vec3\n");
	}
	else
	{
		printf("vec3:\n");
		printf("%f\n", vec.x);
		printf("%f\n", vec.y);
		printf("%f\n", vec.z);
	}
	float f;
	if (get_float(&f, v[2]))
	{
		printf("Error in float\n");
	}
	else
	{
		printf("Float:\n");
		printf("%f\n", f);
	}
	return 0;
}