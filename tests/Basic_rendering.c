#include "Mat4x4.h"
#include "Renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_arrays.h"
#include "input.h"

int	ft_index(const char *s, char c)
{
	unsigned int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}

unsigned int	ft_strlen(const char *str)
{
	unsigned int	num;

	num = 0;
	while (str[num] != '\0')
		num++;
	return (num);
}

char	*ft_strdup(const char *s1)
{
	unsigned int	size;
	char			*ptr;
	int				i;

	size = ft_strlen(s1);
	ptr = malloc((size + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*string;
	size_t	i;
	size_t	x;

	if (!s1)
		s1 = ft_strdup("");
	string = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!string)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	x = 0;
	while (s2[x])
		string[i++] = s2[x++];
	string[i] = 0;
	free(s1);
	return (string);
}
static char	*get_line(char *backup)
{
	int		len;
	int		x;
	char	*line;

	len = 0;
	if (*backup == '\0')
		return (NULL);
	while (backup[len] && backup[len] != '\n')
		len++;
	if (backup[len] == '\n')
		len++;
	line = malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	x = 0;
	while (x < len)
	{
		line[x] = backup[x];
		x++;
	}
	line[x] = '\0';
	return (line);
}

static char	*get_backup(char *backup)
{
	char	*str;
	int		start;
	int		i;

	start = 0;
	while (backup[start] && backup[start] != '\n')
		start++;
	if (backup[start] == '\n')
		start++;
	if (backup[start] == '\0')
	{
		free(backup);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(backup) - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (backup[start])
		str[i++] = backup[start++];
	str[i] = '\0';
	free(backup);
	return (str);
}
static char	*read_line(char *backup, int fd)
{
	int		byte;
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buff)
		return (NULL);
	byte = 1;
	while (byte > 0 && ft_index(backup, '\n') == -1)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte == 0)
			break ;
		if (byte == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[byte] = '\0';
		backup = ft_strjoin(backup, buff);
	}
	free(buff);
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		exit(1);
		return (NULL);
	}
	backup = read_line(backup, fd);
	if (!backup)
		return (NULL);
	line = get_line(backup);
	backup = get_backup(backup);
	return (line);
}
int	f_slen(char *s)
{
	if (!*s)
		return (0);
	return (f_slen(s + 1) + 1);
}
int f_is_rt_file(char *s, char *type)
{
	int	end1;
	int	end2;
	int	count;

	end1 = f_slen(s) - 1;
	end2 = f_slen(type) - 1;
	count = 3;
	while (s[end1] == type[end2] && count)
	{
		end1 --;
		end2 --;
		count --;
	}
	if (!count)
		return (0);
	return (1);
}
int	is_space(char c)
{
	return (c >= 0 && c <= 32);
}
int	check_line(char *line, t_scene *scene, int *rep)
{
	int	i;
	int	item;

	i = 0;
	item = 0;
	//char **parametres = ft_split(line);
	
	while (is_space(*line))
		line ++;
	if (*line == 'A' && is_space(*(line + 1)))
		puts(GREEN"should open fct to fill struct of ambient"rst);// TODO
	else if (*line == 'L' && is_space(*(line + 1)))
		puts(GREEN"should open fct to fill struct of light"rst);// TODO
	else if (*line == 'C' && is_space(*(line + 1)))
		puts(GREEN"should open fct to fill struct of camera"rst);// TODO
	else
		return (ERROR);
	return (0);
}

int	read_file(char *file, t_scene *scene)
{
	char	*line;
	int		fd;
	int		rep;


	line = "";
	rep = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		puts(RED"file doesn't exist ):"rst), exit(1);
	while (line)
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\n')
			break ;
		if (check_line(line, scene, &rep) == ERROR)
			puts(RED"parsing error!"rst), free(line), exit(1);
	}
	free(line);
	close(fd);
	return (0);
}

int	check_args(char *s)
{
	if (!f_is_rt_file(s, ".rt"))
		return (SUCESS);
	else
	{
		printf(RED"should enter rt file :) \n"rst);
		exit (1);
	}
}
int parsing(t_scene *scene, int ac, char **av)
{
	if (ac == 2)
	{
		if (check_args(av[1]) == SUCESS)
			read_file(av[1], scene);
		return (SUCESS);
	}
	else if (ac != 2)
		return (ERROR);
	return (ERROR);
}
void *set_bump_map(void*mlx_ptr, t_object*obj, char*filename)
{
	obj->bump_map.handle = mlx_xpm_file_to_image(mlx_ptr, filename, &obj->bump_map.width, &obj->bump_map.height);
	if (obj->bump_map.handle == NULL)
		return NULL;
	obj->bump_map.data = mlx_get_data_addr(obj->bump_map.handle, &obj->bump_map.bpp, &obj->bump_map.size_line, &obj->bump_map.endian);
	return obj->bump_map.handle;
}
int main(int ac, char **av)
{
	srand(0);
	t_renderer renderer;
	if (ac > 1)
	{
		if (parsing(&renderer.scene, ac, av) == ERROR)
		{
			puts(RED"ERROR"rst);
				exit(1);
		}
	}
	renderer.mlx_context = mlx_init();
	if (renderer.mlx_context == NULL)
	{
		LOG_ERROR("MLX INIT FAILED.");
		return 1;
	}
	renderer.win_width = 1280;
	renderer.win_height = 720;
	renderer.window = mlx_new_window(renderer.mlx_context, renderer.win_width, renderer.win_height, WIN_TITLE);
	if (renderer.window == NULL)
	{
		LOG_ERROR("MLX WINDOW INIT FAILED.");
		return 1;
	}
	renderer.mlx_texture.width = renderer.win_width;
	renderer.mlx_texture.height = renderer.win_height;
	renderer.mlx_texture.handle = mlx_new_image(renderer.mlx_context, renderer.mlx_texture.width, renderer.mlx_texture.height);
	if (renderer.mlx_texture.handle == NULL)
	{
		LOG_ERROR("MLX IMG INIT FAILED.");
		return 1;
	}
	renderer.mlx_texture.data = mlx_get_data_addr(renderer.mlx_texture.handle, &renderer.mlx_texture.bpp, &renderer.mlx_texture.size_line, &renderer.mlx_texture.endian);
	if (renderer.mlx_texture.data == NULL)
	{
		LOG_ERROR("MLX IMG CAN'T GET IMG DATA BUFFER ADDRESS.");
		return 1;
	}
	renderer.scene.camera = new_camera((t_vec3){0, -30, 10}, (t_vec3){0, 1, -.3}, (float)renderer.win_height / renderer.win_width, 120);
	renderer.scene.ambient_color = (t_vec3){1.0f, 1.0f, 1.0f};
	renderer.scene.ambient_intemsity = 0.5f;

	t_darr objects = init_da(sizeof(t_object));
	t_object obj;
	obj = new_cylinder((t_vec3){0.0f, 0, 1.0f}, (t_vec3){0, 50, 0}, (t_vec3){10, 100.5f, 0}, (t_vec3){250.0f, 150.0f, 150.0f});
	add_to_arr(&objects, &obj);
	obj = new_cone((t_vec3){0.0f, 0, 1.0f}, (t_vec3){0, -10, 0}, (t_vec3){4, 5.5f, 0}, (t_vec3){250.0f, 0.0f, 150.0f});
	add_to_arr(&objects, &obj);

	t_darr lights = init_da(sizeof(t_light));
	t_light light;
	light = new_light((t_vec3){20, 0, 10}, .5f, (t_vec3){255.0f, 255.0f, 255.0f});
	add_to_arr(&lights, &light);
	light = new_light((t_vec3){-20, 0, 10}, .7f, (t_vec3){255.0f, 255.0f, 255.0f});
	add_to_arr(&lights, &light);

	renderer.scene.objects = objects.data;
	renderer.scene.objects_count = objects.count;

	renderer.scene.lights = lights.data;
	renderer.scene.lights_count = lights.count;

	for (size_t i = 0; i < renderer.scene.objects_count; i++)
	{
		renderer.scene.objects[i].reflection = 0;
		renderer.scene.objects[i].checkerboard = 0;
	}
	renderer.scene.objects[0].reflection = .7;
	renderer.scene.objects[0].checkerboard = 1;

	renderer.tab_mode = FALSE;
	renderer.redraw = TRUE;
	renderer.selected_obj = NULL;

	set_bump_map(renderer.mlx_context, &renderer.scene.objects[0], "");

	mlx_hook(renderer.window, ON_KEYDOWN, 1L << 0, key_hook_down, &renderer);
	mlx_hook(renderer.window, ON_KEYUP, 1L << 1, key_hook_up, &renderer);
	mlx_loop_hook(renderer.mlx_context, render, &renderer);
	mlx_hook(renderer.window, ON_MOUSEDOWN, 1L << 2, mouse_hook_down, &renderer);
	mlx_hook(renderer.window, ON_MOUSEUP, 1L << 3, mouse_hook_up, &renderer);
	mlx_loop(renderer.mlx_context);
	return 0;
}

/*
		obj = new_plane((t_vec3){0, 0, -1}, (t_vec3){0.0, 0.0, 1.0}, (t_vec3){130.0f, 20.0f, 200.0f});
		add_to_arr(&objects, &obj);

		obj = new_plane((t_vec3){0, 10, 0}, (t_vec3){0.0, -1.0, 0.0}, (t_vec3){10.0f, 50.0f, 100.0f});
		add_to_arr(&objects, &obj);

		obj = new_cone((t_vec3){0.0f, 0.0, 1.0f}, (t_vec3){0, 0, 0}, (t_vec3){2, 2, 0}, (t_vec3){150.0f, 25.0f, 170.0f});
		add_to_arr(&objects, &obj);


		obj = new_rect((t_vec3){5, 2, 2}, (t_vec3){0.0, -1.0, -.2}, (t_vec3){255.0f, 255.0f, 255.0f}, (t_vec3){6.0, 4.0, 0.0});
		add_to_arr(&objects, &obj);
	obj = new_plane((t_vec3){0, 0, -1}, (t_vec3){0.0, 0.0, 1.0}, (t_vec3){130.0f, 20.0f, 200.0f});
	add_to_arr(&objects, &obj);

	obj = new_plane((t_vec3){0, 10, 0}, (t_vec3){0.0, -1.0, 0.0}, (t_vec3){10.0f, 50.0f, 100.0f});
	add_to_arr(&objects, &obj);

	obj = new_sphere((t_vec3){-6, -2, 1}, 4.0f, (t_vec3){255.0f, 0, 0});
	add_to_arr(&objects, &obj);

	obj = new_sphere((t_vec3){0, 0, 0}, .05f, (t_vec3){255.0f, 0, 0});
	add_to_arr(&objects, &obj);

	obj = new_sphere((t_vec3){1, 0, 0}, .05f, (t_vec3){255.0f, 0, 0});
	add_to_arr(&objects, &obj);

	obj = new_sphere((t_vec3){0, 0, 1}, .05f, (t_vec3){255.0f, 0, 0});
	add_to_arr(&objects, &obj);

	obj = new_cylinder((t_vec3){0.0f, 0.0, 1.0f}, (t_vec3){2, -7, 0}, (t_vec3){2, 2, 0}, (t_vec3){10.0f, 125.0f, 70.0f});
	add_to_arr(&objects, &obj);

	obj = new_cylinder((t_vec3){0.0f, 0, 1.0f}, (t_vec3){5, -3, 2}, (t_vec3){6, .5f, 0}, (t_vec3){10.0f, 125.0f, 70.0f});
	add_to_arr(&objects, &obj);

	obj = new_cone((t_vec3){0.0f, 1.0, 0.0f}, (t_vec3){0, 0, 0}, (t_vec3){2, 2, 0}, (t_vec3){150.0f, 25.0f, 170.0f});
	add_to_arr(&objects, &obj);

	obj = new_light((t_vec3){-1, -2, 2}, .4f, (t_vec3){255.0f, 255.0f, 255.0f});
	add_to_arr(&objects, &obj);

	obj = new_light((t_vec3){2, -2, 4.0f}, 0.6f, (t_vec3){255.0f, 255.0f, 255.0f});
	add_to_arr(&objects, &obj);

	obj = new_rect((t_vec3){5, 2, 2}, (t_vec3){0.0, -1.0, -.2}, (t_vec3){255.0f, 255.0f, 255.0f}, (t_vec3){6.0, 4.0, 0.0});
	add_to_arr(&objects, &obj);
*/