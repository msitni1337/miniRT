#ifndef RENDERER_H
#define RENDERER_H
#include "Object.h"
#include <mlx.h>
#include "mlx_utils.h"
#define WIN_TITLE "miniRT"

#define BG_COLOR 0xFF021526

typedef struct s_renderer
{
	t_object* selected_obj;
	void *mlx_context;
	void *window;
	int win_width;
	int win_height;
	t_img mlx_texture;
	t_scene scene;
	int redraw;
	int tab_mode;
} t_renderer;

t_hit get_ray_hit(t_scene *scene, t_ray ray);
t_vec3 get_vec3_color(unsigned int color);

int render(t_renderer *renderer);

// Debug
void print_camera_value(t_camera camera);
void print_object_value(t_object object);

#endif // RENDERER_H
