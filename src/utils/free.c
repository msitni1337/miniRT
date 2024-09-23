#include "utils.h"

void ft_free(void *p1, void *p2, void *p3)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p2);
}