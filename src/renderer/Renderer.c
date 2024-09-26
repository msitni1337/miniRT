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

// TODO: make reflection ray more accurate by setting it to the reflected ray from camera to the hitted point
t_vec3 calculate_reflection_color(t_scene*scene, t_hit hit, t_vec3 hit_color)
{
	t_vec3 result;
	t_ray r_ray;
	t_hit r_hit;
	t_vec3 r_shade;
	t_vec3 r_color;

	result = hit_color;
	r_ray.origin = hit.hit_point;
	r_ray.dir = hit.normal;
	/**/
	/*
	 * Randomize reflection direction to have haizzy effect.
	ref_ray.dir.x += ((((float)rand() / (float)RAND_MAX) / 2) - 1) * 0.025;
	ref_ray.dir.y += ((((float)rand() / (float)RAND_MAX) / 2) - 1) * 0.025;
	ref_ray.dir.z += ((((float)rand() / (float)RAND_MAX) / 2) - 1) * 0.025;
	ref_ray.dir = vec3_normalize(ref_ray.dir);
	*/
	/**/
	r_ray.target = vec3_add_vec3(r_ray.origin, r_ray.dir);
	r_hit = cast_ray(scene, r_ray, FALSE);
	if (r_hit.is_valid && r_hit.object != hit.object)
	{
		r_color = get_object_color(r_hit);
		r_shade = shade_color(scene, r_hit, r_ray);
		r_shade = vec3_mul(r_shade, r_color);
		r_shade = vec3_scale(r_shade, hit.object->reflection);
		//t_vec3 ambient = vec3_mul(scene->ambient_color, r_color);
		//result = vec3_add_vec3(ambient, result);
		result = vec3_scale(hit_color, 1.0f - hit.object->reflection);
		result = vec3_add_vec3(result, r_shade);
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
			color = calculate_reflection_color(scene, hit, color);
		shade = vec3_mul(shade, color);
		color = vec3_mul(scene->ambient_color, color);
		shade = vec3_add_vec3(shade, color);
		pixel_color = get_color_vec3(vec3_cap(shade, 0.0f, 1.0f));
	}
	return pixel_color;
}

int render(t_renderer *renderer)
{
	t_img *img;

	if (renderer->redraw == FALSE)
		return 0;
	log_info("Rendering Image..");
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
	log_info("Finished Image..");
	renderer->redraw = FALSE;
	return 0;
}
