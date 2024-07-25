#include "Renderer.h"

t_hit get_ray_hit(t_scene *scene, t_ray ray)
{
	t_object *object;
	size_t i;
	t_hit hit;
	t_hit tmp;

	i = 0;
	hit.object = NULL;
	hit.data = INFINITY;
	object = get_next_object_by_type(scene, &i, OBJ_SPHERE);
	while (object)
	{
		tmp = object->intersection(object, ray);
		if (tmp.object && (tmp.data - hit.data) < ZERO)
			hit = tmp;
		i++;
		object = get_next_object_by_type(scene, &i, OBJ_SPHERE);
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
		t_vec3 hit_normal = vec3_sub_vec3(hit_point.hit_point, get_object_pos(hit_point.object));
		hit_normal = vec3_normalize(hit_normal);

		t_vec3 light_normal = vec3_sub_vec3(get_object_pos(light), get_object_pos(hit_point.object));
		light_normal = vec3_normalize(light_normal);
		float intensity = vec3_dot(hit_normal, light_normal);
		intensity = float_cap(intensity, 0.0f, 1.0f);

		hit_light.data = intensity;
		hit_light.object = light;
		hit_light.hit_point = hit_normal;
		
		i++;
		light = get_next_object_by_type(scene, &i, OBJ_SPHERE);
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
			
			color_vec = vec3_scale(((t_object*)hit_point.object)->color, hit_light.data);
			color = get_color_vec3(color_vec);
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