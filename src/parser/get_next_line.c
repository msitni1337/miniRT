/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:32:42 by msitni            #+#    #+#             */
/*   Updated: 2024/09/25 10:32:43 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	st_getnl_index(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	if (str && str[i] == '\n')
		return (i);
	return (-1);
}

char	*ft_get_remainder(char **rem)
{
	char	*rem_tmp;
	char	*res;

	if (st_getnl_index(*rem) == -1 || st_getnl_index(*rem)
		+ 1 == ft_strlen(*rem))
	{
		res = ft_substr(*rem, 0, ft_strlen(*rem));
		free(*rem);
		*rem = NULL;
		return (res);
	}
	res = ft_substr(*rem, 0, st_getnl_index(*rem) + 1);
	rem_tmp = ft_substr(*rem, st_getnl_index(*rem) + 1, ft_strlen(*rem));
	free(*rem);
	*rem = rem_tmp;
	if (!rem_tmp)
		return (free_ptr(res, 0, 0, 0));
	return (res);
}

int	st_get_line(char **res, char **rem, int fd, char *tmp)
{
	char	*buff;
	char	*result;
	int		chars_read;

	buff = malloc(BUFFER_SIZE + ((size_t) 1));
	if (!buff)
		return (0 || free_ptr(0, 0, 0, res));
	chars_read = read(fd, buff, BUFFER_SIZE);
	if (chars_read == -1)
		return (0 || free_ptr(0, buff, 0, res));
	buff[chars_read] = 0;
	if (st_getnl_index(buff) != -1)
	{
		tmp = ft_substr(buff, 0, st_getnl_index(buff) + 1);
		result = ft_strjoin(*res, tmp);
		*rem = ft_substr(buff, st_getnl_index(buff) + 1, ft_strlen(buff));
		if (!*rem || !result)
			return (0 || free_ptr(buff, 0, result, res));
	}
	else
		result = ft_strjoin(*res, buff);
	free_ptr(tmp, buff, 0, res);
	*res = result;
	return (chars_read);
}

char	*get_next_line(int fd)
{
	static char	*line_remain;
	char		*res;
	int			bytes_read;

	if (fd < 0)
		return (NULL);
	res = 0;
	while (st_getnl_index(res) == -1)
	{
		if (line_remain)
		{
			res = ft_get_remainder(&line_remain);
			if (!res)
				return (NULL);
			continue ;
		}
		bytes_read = st_get_line(&res, &line_remain, fd, 0);
		if (!res)
			return (NULL);
		if (!bytes_read && !line_remain && (!res || !*res))
			return (free_ptr(res, 0, 0, 0));
		else if (!bytes_read && !line_remain)
			break ;
	}
	return (res);
}
