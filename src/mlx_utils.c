#include "Renderer.h"

void set_img_pixel_at(t_img*img, int x, int y, int color)
{
	char	*tmp;

	tmp = &(img->data[x * (img->bpp / 8) + y * img->size_line]);
	*(unsigned int*)tmp = color;
}