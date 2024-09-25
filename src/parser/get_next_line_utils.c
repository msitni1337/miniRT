#include "get_next_line.h"

void	*free_ptr(void *ptr, void *ptr1, void *ptr2, char **ptr3)
{
	if (ptr)
		free(ptr);
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
	{
		if (*ptr3)
			free(*ptr3);
		*ptr3 = 0;
	}
	return (NULL);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, long start, long len)
{
	char	*str;
	int		i;

	if (len < ft_strlen(s))
		str = malloc(len + 1);
	else
		str = malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i + start] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(s1_len + s2_len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		str[i + s1_len] = s2[i];
		i++;
	}
	str[s1_len + s2_len] = 0;
	return (str);
}
