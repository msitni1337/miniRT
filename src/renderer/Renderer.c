#include "Renderer.h"

t_hit get_ray_hit(t_scene *scene, t_ray ray)
{
	t_object *object;
	size_t i;
	t_hit hit;
	t_hit tmp;

	i = 0;
	hit.object = NULL;
	hit.data = INF;
	object = get_next_object_by_type(scene, &i, OBJ_CYLINDER | OBJ_SPHERE | OBJ_PLANE);
	while (object)
	{
		tmp = object->intersection(object, ray);
		if (tmp.object && (tmp.data < hit.data))
			hit = tmp;
		i++;
		object = get_next_object_by_type(scene, &i, OBJ_CYLINDER | OBJ_SPHERE | OBJ_PLANE);
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

t_hit get_light_hit(t_scene *scene, t_hit hit_point)
{
	t_object *light;
	size_t i;
	t_hit hit_light;
	t_hit tmp;

	i = 0;
	hit_light.object = NULL;
	hit_light.data = 0;
	light = get_next_object_by_type(scene, &i, OBJ_LIGHT);
	while (light)
	{
		t_vec3 hit_normal = hit_point.normal;//((t_object *)hit_point.object)->point_normal(hit_point);

		t_vec3 light_normal = vec3_sub_vec3(get_object_pos(light), hit_point.hit_point);
		light_normal = vec3_normalize(light_normal);

		float intensity = light->intensity * vec3_dot(hit_normal, light_normal);
		intensity = float_cap(intensity, 0.0f, 1.0f);

		hit_light.data = intensity;
		hit_light.object = light;
		hit_light.hit_point = hit_normal;

		t_ray light_ray;
		light_ray.origin = hit_point.hit_point;
		light_ray.target = get_object_pos(light);
		light_ray.dir = vec3_normalize(vec3_sub_vec3(light_ray.target, light_ray.origin));

		t_hit shadow_hit = get_ray_hit(scene, light_ray);
		if (shadow_hit.object)
			hit_light.data = 0.0f;
		i++;
		light = get_next_object_by_type(scene, &i, OBJ_LIGHT);
		/*
			TODO: handle multiple light sources..
		*/
	}
	return hit_light;
}
unsigned int calculate_intersections(t_scene *scene, t_ray ray)
{
	t_hit hit_point;
	t_hit hit_light;
	unsigned int color;

	color = BG_COLOR;
	hit_point = get_ray_hit(scene, ray);
	if (hit_point.object != NULL)
	{
		hit_light = get_light_hit(scene, hit_point);
		if (hit_light.object)
		{
			t_vec3 color_vec;

			color_vec = vec3_scale(vec3_mul(((t_object *)hit_light.object)->color, ((t_object *)hit_point.object)->color)
			, hit_light.data);
			t_vec3 color_vec1 = vec3_mul(vec3_scale(scene->ambient_color, scene->ambient_intemsity), ((t_object *)hit_point.object)->color);
			color_vec = vec3_add_vec3(color_vec, color_vec1);
			color = get_color_vec3(vec3_cap(color_vec, 0.0f, 1.0f));
		}
	}
	return color;
}

int render(t_renderer *renderer)
{
	t_img *img;

	if (renderer->redraw == FALSE)
		return 0;
	img = &(renderer->mlx_texture);
	for (int x = 0; x < renderer->mlx_texture.width; x++)
	{
		for (int y = 0; y < renderer->mlx_texture.height; y++)
		{
			t_ray ray;
			ray = get_ray(&renderer->scene.camera, (t_vec3){x, y}, (t_vec3){img->width, img->height});
			unsigned int color = calculate_intersections(&renderer->scene, ray);
			set_img_pixel_at(&renderer->mlx_texture, x, renderer->mlx_texture.height - y, color);
		}
	}
	mlx_put_image_to_window(renderer->mlx_context, renderer->window, renderer->mlx_texture.handle, 0, 0);
	renderer->redraw = FALSE;
	return 0;
}