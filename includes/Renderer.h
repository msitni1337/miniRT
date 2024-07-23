#ifndef RENDERER_H
#define RENDERER_H
#include "Scene.h"
#include "Ray.h"
//#include <mlx.h>

typedef struct s_img
{
	void *handle;
	char *data;
	int bpp;
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

int render(t_renderer *renderer);
#endif // RENDERER_H
