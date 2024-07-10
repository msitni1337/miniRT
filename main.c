#include "vec3.h"
#include <stdio.h>
#include <stdlib.h>

int main(int c, char**v)
{
	if (c < 4)
		return 1;	
	t_vec3 vec = vec3_i(atoi(v[1]), atoi(v[2]), atoi(v[3]));

	printf("raw (%lf, %lf, %lf)\n", vec.x, vec.y, vec.z);
	vec = vec3_normalize(vec);
	printf("normalized (%lf, %lf, %lf)\n", vec.x, vec.y, vec.z);
}