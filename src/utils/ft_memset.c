/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:21:48 by msitni            #+#    #+#             */
/*   Updated: 2024/09/25 10:21:48 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
