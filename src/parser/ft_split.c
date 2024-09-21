#include "parser.h"

int ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r' || c == '\v');
}

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t ft_strlcpy(char *dst, const char *src, size_t sz)
{
	size_t i;

	i = 0;
	if (!sz)
		return (ft_strlen(src));
	while (src[i] && i < sz - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}

static char **handle_error(char **ptr, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static size_t count_strs(char const *str, int (*delim)(char))
{
	size_t count;
	int i;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		if (delim(str[i]))
		{
			while (str[i] && delim(str[i]))
				i++;
		}
		else
		{
			count++;
			while (str[i] && !delim(str[i]))
				i++;
		}
	}
	return (count);
}

static size_t get_next_str_size(char const *str, int (*delim)(char))
{
	size_t i;

	i = 0;
	while (str && str[i] && !delim(str[i]))
		i++;
	return (i);
}

static char **perform_split(char **res, char const *s, int (*delim)(char))
{
	int index;
	int curr_index;
	char *str;
	size_t str_s;

	curr_index = 0;
	index = 0;
	while (s && s[curr_index])
	{
		str_s = get_next_str_size(s + curr_index, delim);
		if (!str_s)
			curr_index++;
		else
		{
			str = malloc(str_s + 1);
			if (!str)
				return (handle_error(res, index));
			ft_strlcpy(str, s + curr_index, str_s + 1);
			res[index] = str;
			index++;
			curr_index += str_s;
		}
	}
	res[index] = 0;
	return (res);
}

char **ft_split(char const *s, size_t *count, int (*delim)(char))
{
	char **res;

	if (!s)
		return (NULL);
	*count = count_strs(s, delim);
	res = malloc(sizeof(char **) * (*count + 1));
	if (!res)
		return (NULL);
	return (perform_split(res, s, delim));
}