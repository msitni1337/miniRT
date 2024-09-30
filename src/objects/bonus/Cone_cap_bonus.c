/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone_cap_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:28 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:16:48 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.h"

t_hit cone_cap_intersection(t_object *object, t_ray ray)
{
	t_hit hit;
	t_hit cap;

	hit = cone_intersection(object, ray);

	cap = cap_intersection(object->anti_normal, object->position, object->radius, ray);

	if (cap.is_valid && (!hit.is_valid || cap.distance < hit.distance))
	{
		hit.hit_point = cap.hit_point;
		hit.normal = object->anti_normal;
		hit.distance = cap.distance;
		hit.uv_map = cap_map_uv(vec3_sub_vec3(cap.hit_point, object->position), object->orth_normal, object->orth_normal2, object->radius);
		hit.is_valid = TRUE;
	}
	return hit;
}