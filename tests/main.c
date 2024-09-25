#include "input.h"
#include "parser.h"

int main(int c, char **v)
{
	t_renderer r;

	if (c != 2)
	{
		printf("invalid args\n");
		printf("usage: %s [Scene_file_path.rt]\n", v[0]);
		return 1;
	}
	r = (t_renderer){0};
	if (parsing(&r.scene, c, v) == ERROR)
	{
		ft_free(r.scene.objects, r.scene.lights, NULL);
		return 1;
	}
	r.mlx_context = mlx_init();
	if (r.mlx_context == NULL)
	{
		ft_free(r.scene.objects, r.scene.lights, NULL);
		LOG_ERROR("MLX INIT FAILED.");
		return 1;
	}
	r.win_width = WIN_WIDTH;
	r.win_height = WIN_HEIGHT;
	r.window = mlx_new_window(r.mlx_context, r.win_width, r.win_height, WIN_TITLE);
	if (r.window == NULL)
	{
		ft_free(r.scene.objects, r.scene.lights, NULL);
		LOG_ERROR("MLX WINDOW INIT FAILED.");
		return 1;
	}
	r.mlx_texture.width = r.win_width;
	r.mlx_texture.height = r.win_height;
	r.mlx_texture.handle = mlx_new_image(r.mlx_context, r.mlx_texture.width, r.mlx_texture.height);
	if (r.mlx_texture.handle == NULL)
	{
		ft_free(r.scene.objects, r.scene.lights, NULL);
		LOG_ERROR("MLX IMG INIT FAILED.");
		return 1;
	}
	r.mlx_texture.data = mlx_get_data_addr(r.mlx_texture.handle, &r.mlx_texture.bpp, &r.mlx_texture.size_line, &r.mlx_texture.endian);
	if (r.mlx_texture.data == NULL)
	{
		ft_free(r.scene.objects, r.scene.lights, NULL);
		LOG_ERROR("MLX IMG CAN'T GET IMG DATA BUFFER ADDRESS.");
		return 1;
	}
	r.tab_mode = FALSE;
	r.redraw = TRUE;
	r.selected_obj = NULL;
	mlx_hook(r.window, ON_KEYDOWN, 1L << 0, key_hook_down, &r);
	mlx_hook(r.window, ON_KEYUP, 1L << 1, key_hook_up, &r);
	mlx_loop_hook(r.mlx_context, render, &r);
	mlx_hook(r.window, ON_MOUSEDOWN, 1L << 2, mouse_hook_down, &r);
	mlx_hook(r.window, ON_MOUSEUP, 1L << 3, mouse_hook_up, &r);
	mlx_loop(r.mlx_context);
	return 0;
}