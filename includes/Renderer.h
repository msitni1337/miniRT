#ifndef RENDERER_H
#define RENDERER_H
#include "Scene.h"
// #include <mlx.h>
#include "../mlx.h"
#define WIN_TITLE "miniRT"
#define KEY_DOWN 65364
#define KEY_UP 65362
#define KEY_RIGHT 65363
#define KEY_LEFT 65361

typedef struct s_img
{
	void *handle;
	char *data;
	int bpp;
	int size_line;
	int width;
	int height;
	int endian;
} t_img;

typedef struct s_renderer
{
	void *mlx_context;
	void *window;
	int win_width;
	int win_height;
	t_scene scene;
	t_img mlx_texture;
} t_renderer;

void set_img_pixel_at(t_img *img, int x, int y, int color);
int render(t_renderer *renderer);
#endif // RENDERER_H
