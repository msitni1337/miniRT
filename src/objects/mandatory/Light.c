/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:38 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:16:48 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.h"

t_light new_light(t_vec3 position, float intensity, t_vec3 color)
{
    t_light light;

    light.position = position;
    light.color = vec3_scale(color, 1.0f / 255.0f);
    light.intensity = float_cap(intensity, 0.0f, 1.0f);
    return light;
}