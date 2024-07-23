#include "Renderer.h"

int render(t_renderer * renderer)
{
	t_img* img;

	img = &(renderer->mlx_texture);

	for (int x = 0; x < renderer->mlx_texture.width; x++)
		for (int y = 0; y < renderer->mlx_texture.height; y++)
		{
			t_ray ray;
			ray = get_ray(&renderer->scene.camera, (t_vec3) {x, y}, (t_vec3) {img->width, img->height});
			
		}
			
}