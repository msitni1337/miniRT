#ifndef RENDERER_H
#define RENDERER_H
#include "Object.h"
#include <mlx.h>
#define WIN_TITLE "miniRT"
#define KEY_DOWN 65364
#define KEY_UP 65362
#define KEY_RIGHT 65363
#define KEY_LEFT 65361
#define KEY_Z 122
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_8 65431
#define KEY_2 65433
#define KEY_6 65432
#define KEY_4 65430
#define BG_COLOR 0xFF021526

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
	t_img mlx_texture;
	t_scene scene;
	int redraw;
} t_renderer;

void set_img_pixel_at(t_img *img, int x, int y, int color);
int render(t_renderer *renderer);

// Debug
void print_camera_value(t_camera camera);
void print_object_value(t_object object);

#endif // RENDERER_H
