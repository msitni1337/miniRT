#include "parser.h"

int is_valid_color(t_vec3 color)
{
	if (color.x < 0.0f || color.x > 255.0f)
		return TRUE;
	if (color.y < 0.0f || color.y > 255.0f)
		return TRUE;
	if (color.z < 0.0f || color.z > 255.0f)
		return TRUE;
	return FALSE;
}

int is_normalized(t_vec3 vec)
{
	float magnitude;

	magnitude = vec3_magnitude(vec);

	return magnitude >= 0.98 && magnitude <= 1.0f;
}