#include "Renderer.h"

t_hit get_ray_hit(t_scene *scene, t_ray ray)
{
	t_object *object;
	size_t i;
	t_hit hit;
	t_hit tmp;

	i = 0;
	hit.is_valid = FALSE;
	while (i < scene->objects_count)
	{
		object = scene->objects + i;
		tmp = object->intersection(object, ray);
		if (tmp.is_valid && (!hit.is_valid || tmp.distance < hit.distance))
			hit = tmp;
		i++;
	}
	return hit;
}

t_hit get_lighray_hit(t_scene *scene, t_ray ray)
{
	t_object *object;
	size_t i;
	t_hit hit;
	t_hit tmp;

	i = 0;
	hit.is_valid = FALSE;
	while (i < scene->objects_count)
	{
		object = scene->objects + i;
		tmp = object->intersection(object, ray);
		if (tmp.is_valid && (!hit.is_valid || tmp.distance < hit.distance))
			hit = tmp;
		i++;
	}
	return hit;
}

unsigned int get_color_vec3(t_vec3 vec)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = vec.x * 255.0f;
	g = vec.y * 255.0f;
	b = vec.z * 255.0f;
	return (0x00 << 24 | r << 16 | g << 8 | b);
}

t_vec3 get_vec3_color(unsigned int color)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = color >> 16;
	g = color >> 8;
	b = color;
	return (t_vec3){r, g, b};
}

t_vec3 get_light_color(t_scene *scene, t_hit hit_point, t_ray ray)
{
	t_vec3 color = {0};
	t_light *light;
	size_t i;
	t_hit hit_light;
	t_hit tmp;

	i = 0;
	hit_light.is_valid = FALSE;
	// hit_light.object = NULL;
	hit_light.distance = 0;
	while (i < scene->lights_count)
	{
		light = scene->lights + i;
		t_vec3 hit_normal = hit_point.normal;
		t_object *obj = hit_point.object;
		if (obj->normal_map.data != NULL)
		{
			t_vec3 u_vec = vec3_cross(hit_point.normal, ray.dir);
			if (vec3_magnitude(u_vec) > ZERO)
			{
				t_vec3 v_vec = vec3_cross(hit_point.normal, u_vec);
				t_vec3 pixel_coord;
				int x;
				int y;

				x = hit_point.uv_map.x * obj->normal_map.width;
				y = hit_point.uv_map.y * obj->normal_map.height;
				assert(x >= 0 && y >= 0);
				// assert(x < obj->texture.width && y < obj->texture.height);
				x = int_cap(x, 0, obj->normal_map.width - 1);
				y = int_cap(y, 0, obj->normal_map.height - 1);
				t_vec3 tex_color = vec3_scale(get_vec3_color(get_img_pixel_at(&obj->normal_map, x, y)), 1 / 255.0f);

				hit_normal = vec3_add_vec3(vec3_scale(u_vec, (tex_color.x * 2 - 1)), vec3_scale(v_vec, (tex_color.y * 2 - 1)));
				hit_normal = vec3_add_vec3(hit_normal, vec3_scale(hit_point.normal, tex_color.z));
				hit_normal = vec3_add_vec3(hit_normal, hit_point.hit_point);
				hit_normal = vec3_sub_vec3(hit_normal, hit_point.hit_point);
			}
		}

		t_vec3 light_normal = vec3_sub_vec3(light->position, hit_point.hit_point);
		light_normal = vec3_normalize(light_normal);

		float intensity = light->intensity * vec3_dot(hit_normal, light_normal);
		intensity = float_cap(intensity, 0.0f, 1.0f);

		hit_light.distance = intensity;
		hit_light.object = light;
		hit_light.hit_point = hit_normal;

		t_ray light_ray;
		light_ray.origin = light->position;
		light_ray.target = hit_point.hit_point;
		light_ray.dir = vec3_normalize(vec3_sub_vec3(light_ray.target, light_ray.origin));

		t_hit shadow_hit = get_lighray_hit(scene, light_ray);
		if (!shadow_hit.is_valid || shadow_hit.object == hit_point.object)
		{
			color = vec3_add_vec3(color, vec3_scale(light->color, intensity));
		}
		i++;
	}
	return vec3_cap(color, 0.0f, 1.0f);
}

unsigned int calculate_intersections(t_scene *scene, t_ray ray)
{
	t_hit hit_point;
	t_vec3 light_color;
	unsigned int color;

	color = BG_COLOR;
	hit_point = get_ray_hit(scene, ray);
	if (hit_point.is_valid)
	{
		t_object *obj = hit_point.object;
		light_color = get_light_color(scene, hit_point, ray);
		t_vec3 color_vec;
		t_vec3 hit_point_color = obj->color;

		/* CheckerBoard Color mapping */
		if (obj->checkerboard)
		{
			int x;
			int y;

			x = ceil(hit_point.uv_map.z);
			y = ceil(hit_point.uv_map.w);
			if ((y + x) % 2 == 0)
				hit_point_color = (t_vec3){0};
			else
				hit_point_color = (t_vec3){1, 1, 1};
		}
		else if (obj->texture.data != NULL)
		{
			t_vec3 pixel_coord;
			int x;
			int y;

			x = hit_point.uv_map.x * obj->texture.width;
			y = hit_point.uv_map.y * obj->texture.height;
			assert(x >= 0 && y >= 0);
			// assert(x < obj->texture.width && y < obj->texture.height);
			x = int_cap(x, 0, obj->texture.width - 1);
			y = int_cap(y, 0, obj->texture.height - 1);
			unsigned int tex_color = get_img_pixel_at(&obj->texture, x, y);
			hit_point_color = vec3_scale(get_vec3_color(tex_color), 1 / 255.0f);
		}

		/* Reflection Calculations */
		if (obj->reflection > ZERO)
		{
			t_ray ref_ray;
			ref_ray.origin = hit_point.hit_point;
			ref_ray.dir = hit_point.normal;
			/**/
			/*
			 * Randomize reflection direction to have haizzy effect.
			ref_ray.dir.x += ((((float)rand() / (float)RAND_MAX) / 2) - 1) * 0.025;
			ref_ray.dir.y += ((((float)rand() / (float)RAND_MAX) / 2) - 1) * 0.025;
			ref_ray.dir.z += ((((float)rand() / (float)RAND_MAX) / 2) - 1) * 0.025;
			ref_ray.dir = vec3_normalize(ref_ray.dir);
			*/
			/**/
			ref_ray.target = vec3_add_vec3(ref_ray.origin, ref_ray.dir);
			t_hit ref_hit = get_ray_hit(scene, ref_ray);
			if (ref_hit.is_valid && ref_hit.object != hit_point.object)
			{
				t_object *ref_obj = ref_hit.object;
				t_vec3 ref_color;

				ref_color = ref_obj->color;
				if (ref_obj->checkerboard)
				{
					int x;
					int y;

					x = ceil(ref_hit.uv_map.z);
					y = ceil(ref_hit.uv_map.w);
					if ((y + x) % 2 == 0)
						ref_color = (t_vec3){0};
					else
						ref_color = (t_vec3){1, 1, 1};
				}
				else if (ref_obj->texture.data != NULL)
				{
					t_vec3 pixel_coord;
					int x;
					int y;

					x = ref_hit.uv_map.x * ref_obj->texture.width;
					y = ref_hit.uv_map.y * ref_obj->texture.height;
					assert(x >= 0 && y >= 0);
					// assert(x < ref_obj->texture.width && y < ref_obj->texture.height);
					x = int_cap(x, 0, ref_obj->texture.width - 1);
					y = int_cap(y, 0, ref_obj->texture.height - 1);
					unsigned int tex_color = get_img_pixel_at(&ref_obj->texture, x, y);
					ref_color = vec3_scale(get_vec3_color(tex_color), 1 / 255.0f);
				}

				t_vec3 ref_light = get_light_color(scene, ref_hit, ray);
				t_vec3 ambient = vec3_mul(vec3_scale(scene->ambient_color, scene->ambient_intensity), ref_color);
				hit_point_color = vec3_scale(hit_point_color, 1.0f - obj->reflection);
				hit_point_color = vec3_add_vec3(hit_point_color, vec3_scale(vec3_mul(ref_color, ref_light), obj->reflection));
				hit_point_color = vec3_add_vec3(ambient, hit_point_color);
			}
		}
		color_vec = vec3_mul(light_color, hit_point_color);
		t_vec3 color_vec1 = vec3_mul(vec3_scale(scene->ambient_color, scene->ambient_intensity), hit_point_color);
		color_vec = vec3_add_vec3(color_vec, color_vec1);
		color = get_color_vec3(vec3_cap(color_vec, 0.0f, 1.0f));
	}
	return color;
}

int render(t_renderer *renderer)
{
	t_img *img;

	if (renderer->redraw == FALSE)
		return 0;
	LOG_INFO("Rendering Image..");
	img = &(renderer->mlx_texture);
	for (int y = renderer->mlx_texture.height - 1; y >= 0; y--)
	{
		for (int x = 0; x < renderer->mlx_texture.width; x++)
		{
			t_ray ray;
			ray = get_ray(&renderer->scene.camera, (t_vec3){x, y}, (t_vec3){img->width, img->height});
			unsigned int color = calculate_intersections(&renderer->scene, ray);
			// mlx_pixel_put(renderer->mlx_context, renderer->window, x, renderer->mlx_texture.height - y, color);
			set_img_pixel_at(&renderer->mlx_texture, x, renderer->mlx_texture.height - y, color);
		}
		mlx_put_image_to_window(renderer->mlx_context, renderer->window, renderer->mlx_texture.handle, 0, 0);
	}
	LOG_INFO("Finished Image..");
	renderer->redraw = FALSE;
	return 0;
}
