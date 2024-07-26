#include "Object.h"

int main()
{
	t_vec3 orientation = vec3_normalize((t_vec3){0.0f, 0.0f, 0.0f});

	t_mat4x4 orientation_mat = get_euler_rotation_matrix(orientation);
	printf("orientation:\n");
	print_vec3(orientation);
	printf("orientation_mat:\n");
	mat_print(orientation_mat.data, 4);
}