/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_arrays.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:14:30 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:14:40 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_ARRAYS_H
# define DYNAMIC_ARRAYS_H
# define DA_DEFAULT_CAPACITY 5
#include <stddef.h>
#include <stdlib.h>

typedef struct s_darr
{
	void			*data;
	size_t			count;
	size_t			elem_size;
	size_t			capacity;
}					t_darr;

t_darr		init_da(size_t elem_size);
t_darr		*add_to_arr(t_darr *arr, void *data);
t_darr		*expand_arr(t_darr *arr);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif