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

t_vec3 get_light_color(t_scene *scene, t_hit hit_point)
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
		t_vec3 hit_normal = hit_point.normal; //((t_object *)hit_point.object)->point_normal(hit_point);

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

		t_hit shadow_hit = get_ray_hit(scene, light_ray);
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
		light_color = get_light_color(scene, hit_point);
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
				t_vec3 shaded_ref_color = get_light_color(scene, ref_hit);
				t_vec3 ambient = vec3_mul(vec3_scale(scene->ambient_color, scene->ambient_intensity), ref_obj->color);
				hit_point_color = vec3_scale(hit_point_color, 1.0f - obj->reflection);
				hit_point_color = vec3_add_vec3(hit_point_color, vec3_scale(vec3_mul(ref_obj->color, shaded_ref_color), obj->reflection));
				hit_point_color = vec3_add_vec3(ambient, hit_point_color);
			}
			/*
			else
			{
				hit_point_color = (t_vec3){0};
			}
			*/
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
			mlx_pixel_put(renderer->mlx_context, renderer->window, x, renderer->mlx_texture.height - y, color);
			// set_img_pixel_at(&renderer->mlx_texture, x, renderer->mlx_texture.height - y, color);
		}
		// mlx_put_image_to_window(renderer->mlx_context, renderer->window, renderer->mlx_texture.handle, 0, 0);
	}
	LOG_INFO("Finished Image..");
	renderer->redraw = FALSE;
	return 0;
}
