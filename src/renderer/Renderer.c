#include "Renderer.h"

t_vec3 get_object_color(t_hit hit)
{
	t_vec3 pixel_coord;
	t_vec3 color;
	int x;
	int y;

	color = hit.object->color;
	if (hit.object->checkerboard)
	{
		x = ceil(hit.uv_map.z);
		y = ceil(hit.uv_map.w);
		if ((y + x) % 2 == 0)
			color = (t_vec3){0};
		else
			color = (t_vec3){1, 1, 1};
	}
	else if (hit.object->texture.data != NULL)
	{
		x = hit.uv_map.x * hit.object->texture.width;
		y = hit.uv_map.y * hit.object->texture.height;
		x = int_cap(x, 0, hit.object->texture.width - 1);
		y = int_cap(y, 0, hit.object->texture.height - 1);
		x = get_img_pixel_at(&hit.object->texture, x, y);
		color = vec3_scale(get_vec3_color(x), 1 / 255.0f);
	}
	return color;
}

t_vec3 calculate_reflection_color(t_scene *scene, t_hit hit, t_vec3 hit_color, t_vec3 ray_dir)
{
	t_vec3 result;
	t_ray r_ray;
	t_hit r_hit;
	t_vec3 r_shade;
	t_vec3 r_color;

	if (vec3_dot(ray_dir, hit.normal) > ZERO)
		return hit_color;
	t_vec3 u_vec = (t_vec3){0.0f, 0.0f, -1.0f};
	t_vec3 v_vec = vec3_cross(u_vec, hit.normal);
	if (vec3_magnitude(v_vec) < ZERO)
	{
		u_vec = (t_vec3){1.0f, 0.0f, 0.0f};
		v_vec = vec3_cross(u_vec, hit.normal);
	}
	v_vec = vec3_normalize(v_vec);

	r_ray.dir = vec3_scale(u_vec, vec3_dot(ray_dir, u_vec));
	r_ray.origin = vec3_scale(v_vec, vec3_dot(ray_dir, v_vec));
	r_ray.target = vec3_scale(hit.normal, -vec3_dot(ray_dir, hit.normal));
	r_ray.dir = vec3_add_vec3(r_ray.dir, r_ray.origin);
	r_ray.dir = vec3_add_vec3(r_ray.dir, r_ray.target);
	r_ray.dir = vec3_normalize(r_ray.dir);

	r_ray.origin = hit.hit_point;
	/**/
	/*
	 * Randomize reflection direction to have haizzy effect.
	r_ray.dir.x += ((((float)rand() / (float)RAND_MAX) / 2) - 1) * 0.025;
	r_ray.dir.y += ((((float)rand() / (float)RAND_MAX) / 2) - 1) * 0.025;
	r_ray.dir.z += ((((float)rand() / (float)RAND_MAX) / 2) - 1) * 0.025;
	r_ray.dir = vec3_normalize(r_ray.dir);
	*/
	/**/
	r_ray.target = vec3_add_vec3(r_ray.origin, r_ray.dir);
	r_hit = cast_ray(scene, r_ray, FALSE);
	result = hit_color;
	if (r_hit.is_valid && r_hit.object != hit.object)
	{
		r_color = get_object_color(r_hit);
		r_shade = shade_color(scene, r_hit, r_ray);
		r_shade = vec3_mul(r_shade, r_color);
		r_shade = vec3_scale(r_shade, hit.object->reflection);
		result = vec3_scale(hit_color, 1.0f - hit.object->reflection);
		result = vec3_add_vec3(result, r_shade);
		result = vec3_add_vec3(vec3_mul(scene->ambient_color, r_color), result);
	}
	return result;
}

unsigned int calculate_intersections(t_scene *scene, t_ray ray)
{
	t_hit hit;
	t_vec3 color;
	t_vec3 shade;
	unsigned int pixel_color;

	pixel_color = BG_COLOR;
	hit = cast_ray(scene, ray, FALSE);
	if (hit.is_valid)
	{
		shade = shade_color(scene, hit, ray);
		color = get_object_color(hit);
		if (hit.object->reflection > ZERO)
			color = calculate_reflection_color(scene, hit, color, ray.dir);
		shade = vec3_mul(shade, color);
		color = vec3_mul(scene->ambient_color, color);
		shade = vec3_add_vec3(shade, color);
		pixel_color = get_color_vec3(vec3_cap(shade, 0.0f, 1.0f));
	}
	return pixel_color;
}

void render_pass(t_renderer *r)
{
	t_ray ray;
	t_vec3 dimensions;
	int x;
	int y;
	unsigned int color;

	y = r->mlx_texture.height;
	dimensions = (t_vec3){r->mlx_texture.width, r->mlx_texture.height};
	while (y > 0)
	{
		x = 0;
		while (x < r->mlx_texture.width)
		{
			ray = get_ray(&r->scene.camera, (t_vec3){x, y}, dimensions);
			color = calculate_intersections(&r->scene, ray);
			set_img_pixel_at(&r->mlx_texture, x, r->mlx_texture.height - y, color);
			x++;
		}
		y--;
	}
	mlx_put_image_to_window(r->mlx_context, r->window, r->mlx_texture.handle, 0, 0);
}

int render(t_renderer *r)
{
	if (r->redraw == FALSE)
		return 0;
	log_info("Rendering Image..");
	render_pass(r);
	log_info("Finished Image..");
	r->redraw = FALSE;
	return 0;
}
