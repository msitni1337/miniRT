#include "parser.h" 

int contains_other_than(char* str, char*allowed)
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
			{
				i++;
				continue;
			}
			j++;
		}
		return 1;
	}
	return 0;
}

void	ft_atold_fill_precision(const char *nptr, size_t*i, long double *result)
{
	long double	divisor;

	divisor = 10.0f;
	while (nptr[*i] >= '0' && nptr[*i] <= '9')
	{
		*result = *result + (nptr[*i] - '0') / divisor;
		(*i)++;
		divisor *= 10.0f;
	}
}

long double	ft_atold(const char *nptr, size_t *i)
{
	long double	result;
	int			sign;

	sign = 1;
	while (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			sign = -1;
		(*i)++;
	}
	result = 0;
	while (nptr[*i] >= '0' && nptr[*i] <= '9')
	{
		result = result * 10.0f + (nptr[*i] - '0');
		(*i)++;
	}
	if (nptr[*i] != '.')
		return (result * sign);
	(*i)++;
	ft_atold_fill_precision(nptr, i, &result);
	return result * sign;
}


int get_vec3(t_vec3*vec3, char*str)
{
	size_t i;

	if(contains_other_than(str, "0123456789.,+-"))
		return 1;
	i = 0;
	vec3->x = ft_atold(str, &i);
	if (str[i] != ',')
		return 1;
	i++;
	vec3->y = ft_atold(str, &i);
	if (str[i] != ',')
		return 1;
	i++;
	vec3->z = ft_atold(str, &i);
	if (str[i])
		return 1;
	return 0;
}

int get_float(float*f, char*str)
{
	size_t i;

	if(contains_other_than(str, "0123456789.+-"))
		return 1;
	i = 0;
	*f = ft_atold(str, &i);
	if (str[i])
		return 1;
	return 0;
}