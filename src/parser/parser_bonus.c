/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:17:06 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:17:16 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

int fill_ambient(t_scene *scene, char **param, size_t count)
{
	t_vec3 color;
	float intensity;

	if (count != 3)
		return log_error("invalid number of params for ambient light");
	if (get_float(&intensity, param[1]) || intensity < 0 || intensity > 1.0f)
		return log_error("invalid intensity param for ambient light");
	if (get_vec3(&color, param[2]) || is_valid_color(color))
		return log_error("invalid color param for ambient light");
	scene->ambient_color = vec3_scale(color, (1 / 255.0f) * intensity);
	return (0);
}

int fill_light(t_parser *p, char **param, size_t count)
{
	t_light light;
	t_vec3 position;
	float intensity;
	t_vec3 color;

	if (count != 4)
		return log_error("invalid number of params for light");
	if (get_vec3(&position, param[1]))
		return log_error("invalid position param for light");
	if (get_float(&intensity, param[2]) || intensity < 0 || intensity > 1.0f)
		return log_error("invalid intensity param for light");
	if (get_vec3(&color, param[3]) || is_valid_color(color))
		return log_error("invalid color param for light");
	light = new_light(position, intensity, color);
	if (add_to_arr(&p->lights, &light) == NULL)
		return log_error("Malloc failed");
	return (0);
}

int fill_camera(t_scene *scene, char **param, size_t count)
{
	t_vec3 position;
	t_vec3 orientation;
	float fov;

	if (count != 4)
		return log_error("invalid number of params for camera");
	if (get_vec3(&position, param[1]))
		return log_error("invalid position param for camera");
	if (get_vec3(&orientation, param[2]))
		return log_error("invalid orientation param for camera");
	if (get_float(&fov, param[3]) || fov > 180.0f || fov < 0)
		return log_error("invalid fov param for camera");
	scene->camera = new_camera(position, orientation, (float)WIN_HEIGHT / WIN_WIDTH, fov);
	return (0);
}

int fill_object_params(t_object *obj, char **param)
{
	while (param && *param)
	{
		if (ft_strcmp(*param, "-c") == 0)
		{
			obj->checkerboard = TRUE;
		}
		else if (ft_strcmp(*param, "-h") == 0)
		{
			obj->hidden = TRUE;
		}
		else if (ft_strcmp(*param, "-r") == 0)
		{
			param++;
			if (get_float(&obj->reflection, *param) || obj->reflection < 0 || obj->reflection > 1.0f)
				return log_error("provide a reflection value [0.0 ~ 1.0].");
		}
		else if (ft_strcmp(*param, "-t") == 0)
		{
			param++;
			if (param == NULL)
				return log_error("provide a path to the xpm texture img.");
			obj->texture.filename = ft_strdup(*param);
			if (obj->texture.filename == NULL)
				return log_error("Malloc failed");
		}
		else if (ft_strcmp(*param, "-n") == 0)
		{
			param++;
			if (param == NULL)
				return log_error("provide a path to the xpm normal map.");
			obj->normal_map.filename = ft_strdup(*param);
			if (obj->normal_map.filename == NULL)
				return log_error("Malloc failed");
		}
		param++;
	}
	return 0;
}

int fill_sphere(t_parser *p, char **param, size_t count)
{
	t_object object;
	t_vec3 position;
	float diameter;
	t_vec3 color;

	if (count < 4)
		return log_error("invalid number of params for sphere");
	if (get_vec3(&position, param[1]))
		return log_error("invalid position param for sphere");
	if (get_float(&diameter, param[2]) || diameter < 0)
		return log_error("invalid diameter param for sphere");
	if (get_vec3(&color, param[3]) || is_valid_color(color))
		return log_error("invalid color param for sphere");
	object = new_sphere(position, diameter / 2, color);
	if (count > 4 && fill_object_params(&object, param + 4))
		return 1;
	if (add_to_arr(&p->objects, &object) == NULL)
		return log_error("Malloc failed");
	return (0);
}

int fill_plane(t_parser *p, char **param, size_t count)
{
	t_object object;
	t_vec3 point;
	t_vec3 normal;
	t_vec3 color;

	if (count < 4)
		return log_error("invalid number of params for plane");
	if (get_vec3(&point, param[1]))
		return log_error("invalid point param for plane");
	if (get_vec3(&normal, param[2]) || vec3_magnitude(normal) <= ZERO)
		return log_error("invalid normal param for plane");
	if (get_vec3(&color, param[3]) || is_valid_color(color))
		return log_error("invalid color param for plane");
	object = new_plane(point, normal, color);
	if (count > 4 && fill_object_params(&object, param + 4))
		return 1;
	if (add_to_arr(&p->objects, &object) == NULL)
		return log_error("Malloc failed");
	return (0);
}

int fill_cylinder(t_parser *p, char **param, size_t count)
{
	t_object o;
	t_vec3 height_diam;

	if (count < 6)
		return log_error("invalid number of params for cylinder");
	if (get_vec3(&o.position, param[1]))
		return log_error("invalid point param for cylinder");
	if (get_vec3(&o.normal, param[2]) || vec3_magnitude(o.normal) <= ZERO)
		return log_error("invalid normal param for cylinder");
	if (get_float(&height_diam.x, param[3]) || height_diam.x < 0)
		return log_error("invalid height param for cylinder");
	if (get_float(&height_diam.y, param[4]) || height_diam.y < 0)
		return log_error("invalid diameter param for cylinder");
	if (get_vec3(&o.color, param[5]) || is_valid_color(o.color))
		return log_error("invalid color param for cylinder");
	o = new_cylinder(o.normal, o.position, height_diam, o.color);
	if (count > 6 && fill_object_params(&o, param + 6))
		return 1;
	if (add_to_arr(&p->objects, &o) == NULL)
		return log_error("Malloc failed");
	return (0);
}

int fill_rect(t_parser *p, char **param, size_t count)
{
	t_object o;
	t_vec3 height_width;

	if (count < 6)
		return log_error("invalid number of params for rectangle");
	if (get_vec3(&o.position, param[1]))
		return log_error("invalid point param for rectangle");
	if (get_vec3(&o.normal, param[2]) || vec3_magnitude(o.normal) <= ZERO)
		return log_error("invalid normal param for rectangle");
	if (get_float(&height_width.x, param[3]) || height_width.x < 0)
		return log_error("invalid width param for rectangle");
	if (get_float(&height_width.y, param[4]) || height_width.y < 0)
		return log_error("invalid height param for rectangle");
	if (get_vec3(&o.color, param[5]) || is_valid_color(o.color))
		return log_error("invalid color param for rectangle");
	o = new_rect(o.position, o.normal, o.color, height_width);
	if (count > 6 && fill_object_params(&o, param + 6))
		return 1;
	if (add_to_arr(&p->objects, &o) == NULL)
		return log_error("Malloc failed");
	return (0);
}

int fill_cone(t_parser *p, char **param, size_t count)
{
	t_object o;
	t_vec3 height_diam;

	if (count < 6)
		return log_error("invalid number of params for non cap cone");
	if (get_vec3(&o.position, param[1]))
		return log_error("invalid point param for non cap cone");
	if (get_vec3(&o.normal, param[2]) || vec3_magnitude(o.normal) <= ZERO)
		return log_error("invalid normal param for non cap cone");
	if (get_float(&height_diam.x, param[3]) || height_diam.x < 0)
		return log_error("invalid height param for non cap cone");
	if (get_float(&height_diam.y, param[4]) || height_diam.y < 0)
		return log_error("invalid diameter param for non cap cone");
	if (get_vec3(&o.color, param[5]) || is_valid_color(o.color))
		return log_error("invalid color param for non cap cone");
	o = new_cone(o.normal, o.position, height_diam, o.color);
	if (count > 6 && fill_object_params(&o, param + 6))
		return 1;
	if (add_to_arr(&p->objects, &o) == NULL)
		return log_error("Malloc failed");
	return (0);
}

int fill_cone_cap(t_parser *p, char **param, size_t count)
{
	t_object o;
	t_vec3 height_diam;

	if (count < 6)
		return log_error("invalid number of params for capped cone");
	if (get_vec3(&o.position, param[1]))
		return log_error("invalid point param for capped cone");
	if (get_vec3(&o.normal, param[2]) || vec3_magnitude(o.normal) <= ZERO)
		return log_error("invalid normal param for capped cone");
	if (get_float(&height_diam.x, param[3]) || height_diam.x < 0)
		return log_error("invalid height param for capped cone");
	if (get_float(&height_diam.y, param[4]) || height_diam.y < 0)
		return log_error("invalid diameter param for capped cone");
	if (get_vec3(&o.color, param[5]) || is_valid_color(o.color))
		return log_error("invalid color param for capped cone");
	o = new_cone_cap(o.normal, o.position, height_diam, o.color);
	if (count > 6 && fill_object_params(&o, param + 6))
		return 1;
	if (add_to_arr(&p->objects, &o) == NULL)
		return log_error("Malloc failed");
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
	if (ft_strcmp(param[0], "C") == 0)
	{
		if (fill_camera(scene, param, count))
			return free_array(param), ERROR;
		parser->camera_count++;
	}
	else if (ft_strcmp(param[0], "A") == 0)
	{
		if (fill_ambient(scene, param, count))
			return free_array(param), ERROR;
		parser->ambient_count++;
	}
	else if (ft_strcmp(param[0], "L") == 0)
	{
		if (fill_light(parser, param, count))
			return free_array(param), ERROR;
	}
	else if (ft_strcmp(param[0], "sp") == 0)
	{
		if (fill_sphere(parser, param, count))
			return free_array(param), ERROR;
	}
	else if (ft_strcmp(param[0], "pl") == 0)
	{
		if (fill_plane(parser, param, count))
			return free_array(param), ERROR;
	}
	else if (ft_strcmp(param[0], "cy") == 0)
	{
		if (fill_cylinder(parser, param, count))
			return free_array(param), ERROR;
	}
	else if (ft_strcmp(param[0], "rc") == 0)
	{
		if (fill_rect(parser, param, count))
			return free_array(param), ERROR;
	}
	else if (ft_strcmp(param[0], "co") == 0)
	{
		if (fill_cone(parser, param, count))
			return free_array(param), ERROR;
	}
	else if (ft_strcmp(param[0], "cc") == 0)
	{
		if (fill_cone_cap(parser, param, count))
			return free_array(param), ERROR;
	}
	else
	{
		log_error("invalid line");
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
		return log_error("Scene file doesn't exist ):"), 1;
	line_num = 1;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '#' && check_line(line, scene, parser) == ERROR)
		{
			while (line)
			{
				free(line);
				line = get_next_line(fd);
			}
			close(fd);
			return printf(RED "=: Error in line: %zu\n" rst, line_num), 1;
		}
		free(line);
		line = get_next_line(fd);
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
		log_error("should enter .rt file :)");
		return (ERROR);
	}
}

int parsing(t_scene *scene, char **av)
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
		if (p.ambient_count != 0 && p.camera_count != 0 && p.lights.count != 0)
			return SUCESS;
		log_error("One or more Capital param is missing");
		log_error("Capital params are [Camera, Ambient light, Light]");
	}
	return ERROR;
}
