/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:57:48 by msitni            #+#    #+#             */
/*   Updated: 2024/09/25 10:20:54 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

int	main(int c, char **v)
{
	t_renderer	r;

	if (c != 2)
	{
		log_error("invalid args");
		printf(YELLOW "usage: %s [Scene_file_path.rt]\n" rst, v[0]);
		return (1);
	}
	r = (t_renderer){0};
	if (parsing(&r.scene, c, v) == ERROR)
	{
		free_textures_filenames(&r.scene);
		ft_free(r.scene.objects, r.scene.lights, NULL);
		return (2);
	}
	if (start_mlx(&r))
		return (3);
	free_all(&r);
	return (0);
}
