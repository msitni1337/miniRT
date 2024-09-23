#include "parser.h"

int contains_other_than(char *str, char *allowed)
{
	int i;
	int j;

	if (str == NULL)
		return 1;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (allowed[j])
		{
			if (str[i] == allowed[j])
				break;
			j++;
		}
		if (str[i] != allowed[j])
			return 1;
		i++;
	}
	return 0;
}

size_t ft_atof_fill_precision(const char *nptr, size_t i, float *result, int sign)
{
	long double divisor;

	i++;
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (0);
	divisor = 10.0f;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		*result = *result + (nptr[i] - '0') / divisor;
		i++;
		divisor *= 10.0f;
	}
	*result *= sign;
	return i;
}

size_t ft_atof(const char *nptr, float *result)
{
	size_t i;
	int sign;

	i = 0;
	sign = 1;
	while (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (0);
	*result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		*result = *result * 10.0f + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] == '.')
		return ft_atof_fill_precision(nptr, i, result, sign);
	*result *= sign;
	return (i);
}

int get_vec3(t_vec3 *vec3, char *str)
{
	size_t parsed;
	size_t i;

	if (contains_other_than(str, "0123456789.,+-"))
		return 1;
	i = 0;
	parsed = ft_atof(str, &vec3->x);
	if (parsed == 0 || str[i + parsed] != ',')
		return 1;
	i += parsed + 1;
	parsed = ft_atof(str + i, &vec3->y);
	if (parsed == 0 || str[i + parsed] != ',')
		return 1;
	i += parsed + 1;
	parsed = ft_atof(str + i, &vec3->z);
	if (parsed == 0 || str[i + parsed])
		return 1;
	return 0;
}

int get_float(float *f, char *str)
{
	size_t parsed;

	if (contains_other_than(str, "0123456789.+-"))
		return 1;
	parsed = ft_atof(str, f);
	if (parsed == 0 || str[parsed])
		return 1;
	return 0;
}