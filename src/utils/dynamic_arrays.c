/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:21:41 by msitni            #+#    #+#             */
/*   Updated: 2024/09/25 10:21:42 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_arrays.h"

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
