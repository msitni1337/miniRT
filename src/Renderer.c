#include "Renderer.h"

unsigned int calculate_intersections(t_renderer *renderer, t_ray ray)
{
	t_object *object;

	object = &renderer->scene.objects;
	while (object)
	{
		t_hit hit = object->intersection(object, ray);
		if (hit.count)
		{
			unsigned char r = object->color.x * 255.0f;
			unsigned char g = object->color.y * 255.0f;
			unsigned char b = object->color.z * 255.0f;
			return (0x00 << 24 | r << 16 | g << 8 | b);
		}
		break;
	}
	return 0xFF551155;
}

int render(t_renderer *renderer)
{
	t_img *img;
	img = &(renderer->mlx_texture);

	for (int x = 0; x < renderer->mlx_texture.width; x++)
	{
		for (int y = 0; y < renderer->mlx_texture.height; y++)
		{
			t_ray ray;
			ray = get_ray(&renderer->scene.camera, (t_vec3){x, y}, (t_vec3){img->width, img->height});
			unsigned int color = calculate_intersections(renderer, ray);
			set_img_pixel_at(&renderer->mlx_texture, x, y, color);
		}
	}
	mlx_put_image_to_window(renderer->mlx_context, renderer->window,renderer->mlx_texture.handle, 0, 0);
	return 0;
}