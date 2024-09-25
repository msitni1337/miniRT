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

char	*ft_strdup(const char *s)
{
	char	*res;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	res = malloc(s_len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	return (res);
}


int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (s1 && s1 == s2)
		return (0);
	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1 && s2)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (1);
}