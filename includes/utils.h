/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:15:24 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:15:33 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H
#include "Object.h"
#include <stdlib.h>

void ft_free(void *p1, void *p2, void *p3);
void *free_till(char **ptr, int index);
void free_textures_filenames(t_scene* scene);
void free_objects_textures(void *mlx, t_object *objs, size_t count);

#endif // UTILS_H