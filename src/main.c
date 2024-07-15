#include "Mat4x4.h"
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

int main(int c, char**v)
{
	(void)c;
	(void)v;
	t_mat4x4 id;

	id = mat_id();
	mat_print(&id);
}