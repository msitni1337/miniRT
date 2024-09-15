#ifndef RENDERER_H
#define RENDERER_H
#include "Object.h"
<<<<<<< HEAD
#include "../mlx.h"
=======
#include <unistd.h>
#include <fcntl.h>
#include <mlx.h>
#include <stdio.h>
>>>>>>> 9443dd4 (not yet)
#include "mlx_utils.h"
#define WIN_TITLE "miniRT"

#define BG_COLOR 0xFF021526
#define rst   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define SUCESS 0
#define ERROR 1
# define BUFFER_SIZE 42


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

void set_img_pixel_at(t_img *img, int x, int y, int color);
int render(t_renderer *renderer);

// Debug
void print_camera_value(t_camera camera);
void print_object_value(t_object object);

#endif // RENDERER_H
