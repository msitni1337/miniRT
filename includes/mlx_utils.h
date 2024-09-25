#ifndef MLX_UTILS_H
#define MLX_UTILS_H
#include <mlx.h>
//#include "mlx.h"

typedef struct s_img
{
	char*filename;
	void *handle;
	char *data;
	int bpp;
	int size_line;
	int width;
	int height;
	int endian;
} t_img;

void set_img_pixel_at(t_img *img, int x, int y, int color);
unsigned int get_img_pixel_at(t_img*img, int x, int y);


#endif // MLX_UTILS_H