#include "dynamic_arrays.h"

static void	*ft_fmemcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

static void	*ft_rmemcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = n;
	while (i--)
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (dest == src)
		return (dest);
	if (dest < src || src + n <= dest)
		return (ft_fmemcpy(dest, src, n));
	else
		return (ft_rmemcpy(dest, src, n));
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(((unsigned char *)s) + i) = (unsigned char)c;
		i++;
	}
	return (s);
}

t_darr	init_da(size_t elem_size)
{
	t_darr	res;

	res.elem_size = elem_size;
	res.capacity = 0;
	res.count = 0;
	res.data = NULL;
	return (res);
}

t_darr	*expand_arr(t_darr *arr)
{
	void	*tmp;

	if (arr == NULL)
		return (NULL);
	arr->capacity += DA_DEFAULT_CAPACITY;
	tmp = malloc(arr->capacity * arr->elem_size);
	if (tmp == NULL)
		return (NULL);
	ft_memset(tmp, 0, arr->elem_size * arr->capacity);
	if (arr->data && arr->count)
		ft_memcpy(tmp, arr->data, arr->elem_size * arr->count);
	if (arr->data)
		free(arr->data);
	arr->data = tmp;
	return (arr);
}

t_darr	*add_to_arr(t_darr *arr, void *data)
{
	if (arr->capacity == 0 || arr->count >= arr->capacity - 1)
	{
		if (expand_arr(arr) == NULL)
			return (NULL);
	}
	ft_memcpy(((unsigned char *)arr->data) + arr->elem_size * arr->count, data,
		arr->elem_size);
	arr->count++;
	return (arr);
}