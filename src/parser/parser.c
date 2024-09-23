#include "parser.h"

int ft_index(const char *s, char c)
{
	unsigned int i;

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

char *ft_strdup(const char *s1)
{
	unsigned int size;
	char *ptr;
	int i;

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

char *ft_strjoin(char *s1, char const *s2)
{
	char *string;
	size_t i;
	size_t x;

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
static char *get_line(char *backup)
{
	int len;
	int x;
	char *line;

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

static char *get_backup(char *backup)
{
	char *str;
	int start;
	int i;

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
static char *read_line(char *backup, int fd)
{
	int byte;
	char *buff;

	buff = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buff)
		return (NULL);
	byte = 1;
	while (byte > 0 && ft_index(backup, '\n') == -1)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte == 0)
			break;
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

char *get_next_line(int fd)
{
	static char *backup;
	char *line;

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

int is_valid_color(t_vec3 color)
{
	if (color.x < 0.0f || color.x > 255.0f)
		return TRUE;
	if (color.y < 0.0f || color.y > 255.0f)
		return TRUE;
	if (color.z < 0.0f || color.z > 255.0f)
		return TRUE;
	return FALSE;
}

int is_normalized(t_vec3 vec)
{
	float magnitude;

	magnitude = vec3_magnitude(vec);

	return magnitude >= 0.98 && magnitude <= 1.0f;
}

int fill_ambient(t_scene *scene, char **param, size_t count)
{
	t_vec3 color;
	float intensity;

	if (count != 3)
		return puts(RED "invalid number of params for ambient light" rst);
	if (get_float(&intensity, param[1]) || intensity < 0 || intensity > 1.0f)
		return puts(RED "invalid intensity param for ambient light" rst);
	if (get_vec3(&color, param[2]) || is_valid_color(color))
		return puts(RED "invalid color param for ambient light" rst);
	scene->ambient_color = vec3_scale(color, 1 / 255.0f);
	scene->ambient_intensity = intensity;
	return (0);
}

int fill_light(t_parser *p, char **param, size_t count)
{
	t_light light;
	t_vec3 position;
	float intensity;
	t_vec3 color;

	if (count != 4)
		return puts(RED "invalid number of params for light" rst);
	if (get_vec3(&position, param[1]))
		return puts(RED "invalid position param for light" rst);
	if (get_float(&intensity, param[2]) || intensity < 0 || intensity > 1.0f)
		return puts(RED "invalid intensity param for light" rst);
	if (get_vec3(&color, param[3]) || is_valid_color(color))
		return puts(RED "invalid color param for light" rst);
	light = new_light(position, intensity, color);
	if (add_to_arr(&p->lights, &light) == NULL)
		return puts(RED "Malloc failed" rst);
	return (0);
}

int fill_camera(t_scene *scene, char **param, size_t count)
{
	t_vec3 position;
	t_vec3 orientation;
	float fov;

	if (count != 4)
		return puts(RED "invalid number of params for camera" rst);
	if (get_vec3(&position, param[1]))
		return puts(RED "invalid position param for camera" rst);
	if (get_vec3(&orientation, param[2]) || is_normalized(orientation) == 0)
		return puts(RED "invalid orientation param for camera" rst);
	if (get_float(&fov, param[3]) || fov > 180.0f || fov < 0)
		return puts(RED "invalid fov param for camera" rst);
	scene->camera = new_camera(position, orientation, (float)WIN_HEIGHT / WIN_WIDTH, fov);
	return (0);
}

int fill_sphere(t_parser *p, char **param, size_t count)
{
	t_object object;
	t_vec3 position;
	float diameter;
	t_vec3 color;

	if (count != 4)
		return puts(RED "invalid number of params for sphere" rst);
	if (get_vec3(&position, param[1]))
		return puts(RED "invalid position param for sphere" rst);
	if (get_float(&diameter, param[2]) || diameter < 0)
		return puts(RED "invalid diameter param for sphere" rst);
	if (get_vec3(&color, param[3]) || is_valid_color(color))
		return puts(RED "invalid color param for sphere" rst);
	object = new_sphere(position, diameter / 2, color);
	if (add_to_arr(&p->objects, &object) == NULL)
		return puts(RED "Malloc failed" rst);
	return (0);
}

int fill_plane(t_parser *p, char **param, size_t count)
{
	t_object object;
	t_vec3 point;
	t_vec3 normal;
	t_vec3 color;

	if (count != 4)
		return puts(RED "invalid number of params for plane" rst);
	if (get_vec3(&point, param[1]))
		return puts(RED "invalid point param for plane" rst);
	if (get_vec3(&normal, param[2]) || is_normalized(normal) == 0)
		return puts(RED "invalid normal param for plane" rst);
	if (get_vec3(&color, param[3]) || is_valid_color(color))
		return puts(RED "invalid color param for plane" rst);
	object = new_plane(point, normal, color);
	if (add_to_arr(&p->objects, &object) == NULL)
		return puts(RED "Malloc failed" rst);
	return (0);
}

int fill_cylinder(t_parser *p, char **param, size_t count)
{
	t_object o;
	t_vec3 height_diam;

	if (count != 6)
		return puts(RED "invalid number of params for cylinder" rst);
	if (get_vec3(&o.position, param[1]))
		return puts(RED "invalid point param for cylinder" rst);
	if (get_vec3(&o.normal, param[2]) || is_normalized(o.normal) == 0)
		return puts(RED "invalid normal param for cylinder" rst);
	if (get_float(&height_diam.x, param[3]) || height_diam.x < 0)
		return puts(RED "invalid height param for cylinder" rst);
	if (get_float(&height_diam.y, param[4]) || height_diam.y < 0)
		return puts(RED "invalid diameter param for cylinder" rst);
	if (get_vec3(&o.color, param[5]) || is_valid_color(o.color))
		return puts(RED "invalid color param for cylinder" rst);
	o = new_cylinder(o.normal, o.position, height_diam, o.color);
	if (add_to_arr(&p->objects, &o) == NULL)
		return puts(RED "Malloc failed" rst);
	return (0);
}

void free_array(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}

int check_line(char *line, t_scene *scene, t_parser *parser)
{
	char **param;
	size_t count;

	param = ft_split(line, &count, &ft_isspace);
	if (count == 0)
		return free_array(param), SUCESS;
	if (strcmp(param[0], "C") == 0)
	{
		if (fill_camera(scene, param, count))
			return free_array(param), ERROR;
		parser->camera_count++;
	}
	else if (strcmp(param[0], "A") == 0)
	{
		if (fill_ambient(scene, param, count))
			return free_array(param), ERROR;
		parser->ambient_count++;
	}
	else if (strcmp(param[0], "L") == 0)
	{
		if (fill_light(parser, param, count))
			return free_array(param), ERROR;
		parser->light_count++;
	}
	else if (strcmp(param[0], "sp") == 0)
	{
		if (fill_sphere(parser, param, count))
			return free_array(param), ERROR;
	}
	else if (strcmp(param[0], "pl") == 0)
	{
		if (fill_plane(parser, param, count))
			return free_array(param), ERROR;
	}
	else if (strcmp(param[0], "cy") == 0)
	{
		if (fill_cylinder(parser, param, count))
			return free_array(param), ERROR;
	}
	else
	{
		puts(RED "invalid line" rst);
		return free_array(param), ERROR;
	}
	if (parser->ambient_count > 1 || parser->camera_count > 1 || parser->light_count > 1)
	{
		puts(RED "multiple Capital params" rst);
		return free_array(param), ERROR;
	}
	return free_array(param), SUCESS;
}

int read_file(char *file, t_scene *scene, t_parser *parser)
{
	size_t line_num;
	char *line;
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return puts(RED "file doesn't exist ):" rst), 1;
	line_num = 1;
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (check_line(line, scene, parser) == ERROR)
		{
			free(line);
			return printf(RED "error in line: %zu" rst "\n", line_num), 1;
		}
		free(line);
		line_num++;
	}
	close(fd);
	return (0);
}

int f_slen(char *s)
{
	if (!*s)
		return (0);
	return (f_slen(s + 1) + 1);
}

int f_is_rt_file(char *s, char *type)
{
	int end1;
	int end2;
	int count;

	end1 = f_slen(s) - 1;
	end2 = f_slen(type) - 1;
	count = 3;
	while (end1 >= 0 && end2 >= 0 && s[end1] == type[end2] && count)
	{
		end1--;
		end2--;
		count--;
	}
	if (!count)
		return (0);
	return (1);
}

int check_args(char *s)
{
	char *type;

	type = ".rt";
	if (!f_is_rt_file(s, type))
		return (SUCESS);
	else
	{
		printf(RED "should enter .rt file :) \n" rst);
		return (ERROR);
	}
}

int parsing(t_scene *scene, int ac, char **av)
{
	t_parser p;

	p = (t_parser){0};
	p.lights = init_da(sizeof(t_light));
	p.objects = init_da(sizeof(t_object));
	if (check_args(av[1]) == SUCESS)
	{
		if (read_file(av[1], scene, &p))
			return ft_free(p.lights.data, p.objects.data, NULL), ERROR;
		scene->objects_count = p.objects.count;
		scene->objects = p.objects.data;
		scene->lights_count = p.lights.count;
		scene->lights = p.lights.data;
		if (p.ambient_count != 0 && p.camera_count != 0 && p.light_count != 0)
			return SUCESS;
	}
	puts(RED "One or more Capital param is missing" rst);
	return ERROR;
}
