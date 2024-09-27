/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:18:02 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:18:04 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer.h"

t_vec3 shift_by_normal_map(t_object* obj, t_hit hit, t_ray ray)
{
	t_vec3 normal;
	t_vec3 u_vec;
	t_vec3 v_vec;
	t_vec3 pixel;

	normal = hit.normal;
	u_vec = vec3_cross(hit.normal, ray.dir);
	if (vec3_magnitude(u_vec) > ZERO)
	{
		v_vec = vec3_cross(hit.normal, u_vec);
		pixel.x = hit.uv_map.x * obj->normal_map.width;
		pixel.y = hit.uv_map.y * obj->normal_map.height;
		pixel.x = int_cap(pixel.x, 0, obj->normal_map.width - 1);
		pixel.y = int_cap(pixel.y, 0, obj->normal_map.height - 1);
		pixel = vec3_scale(get_vec3_color(get_img_pixel_at(&obj->normal_map, pixel.x, pixel.y)), 1 / 255.0f);
		normal = vec3_add_vec3(vec3_scale(u_vec, (pixel.x * 2 - 1)), vec3_scale(v_vec, (pixel.y * 2 - 1)));
		normal = vec3_add_vec3(normal, vec3_scale(hit.normal, pixel.z));
		normal = vec3_add_vec3(normal, hit.hit_point);
		normal = vec3_sub_vec3(normal, hit.hit_point);
		normal = vec3_normalize(normal);
	}
	return normal;
}

float calculate_light_intensity(t_light*light, t_hit hit)
{
	t_vec3 light_normal;
	float intensity;

	light_normal = vec3_sub_vec3(light->position, hit.hit_point);
	light_normal = vec3_normalize(light_normal);
	intensity = light->intensity * vec3_dot(hit.normal, light_normal);
    assert(intensity <= 1.0f);
	intensity = float_cap(intensity, 0.0f, 1.0f);
	return intensity;
}

int is_not_in_shadow(t_scene*scene, t_light*light, t_hit hit)
{
	t_ray light_ray;
	t_hit shadow_hit;

	light_ray.origin = light->position;
	light_ray.target = hit.hit_point;
	light_ray.dir = vec3_normalize(vec3_sub_vec3(light_ray.target, light_ray.origin));
	shadow_hit = cast_ray(scene, light_ray, TRUE);
	return !shadow_hit.is_valid || shadow_hit.object == hit.object;
}

t_vec3 shade_color(t_scene *scene, t_hit hit, t_ray ray)
{
	t_vec3 shaded_color;
	float intensity;
	t_light *light;
	size_t i;

	i = 0;
	shaded_color = (t_vec3){0};
	while (i < scene->lights_count)
	{
		light = scene->lights + i;
		if (is_not_in_shadow(scene, light, hit))
		{
			if (hit.object->normal_map.data != NULL)
				hit.normal = shift_by_normal_map(hit.object, hit, ray);
			intensity = calculate_light_intensity(light, hit);
			shaded_color = vec3_add_vec3(shaded_color, vec3_scale(light->color, intensity));
		}
		i++;
	}
	return vec3_cap(shaded_color, 0.0f, 1.0f);
}