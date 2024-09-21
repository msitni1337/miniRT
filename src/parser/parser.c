#include "parser.h" 
#include <stdlib.h>

int			ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int		count_words(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str && !ft_isspace(*str))
		{
			count++;
			while (*str && !ft_isspace(*str))
				str++;
		}
	}
	return (count);
}

char	*malloc_word(char *str)
{
	char *word;
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, size_t *count)
{
	char **arr = (char **)malloc(sizeof(char *) * (count_words(str) + 1));
	
    size_t i = 0;
    *count = 0;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str && !ft_isspace(*str))
		{
			arr[i] = malloc_word(str);
			i++;
			while (*str && !ft_isspace(*str))
				str++;
		}
	}
	arr[i] = NULL;
    *count = i;
	return (arr);
}
//
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
void *set_bump_map(void*mlx_ptr, t_object*obj, char*filename)
{
	obj->bump_map.handle = mlx_xpm_file_to_image(mlx_ptr, filename, &obj->bump_map.width, &obj->bump_map.height);
	if (obj->bump_map.handle == NULL)
		return NULL;
	obj->bump_map.data = mlx_get_data_addr(obj->bump_map.handle, &obj->bump_map.bpp, &obj->bump_map.size_line, &obj->bump_map.endian);
	return obj->bump_map.handle;
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
	while (end1 >= 0 && end2 >= 0 && s[end1] == type[end2] && count)
	{
		end1 --;
		end2 --;
		count --;
	}
	if (!count)
		return (0);
	return (1);
}

t_vec3 get_vec3(char *p)
{
    (void)p;
    t_vec3  t;
    return (t);
}

// int    fill_camera(char **param, size_t count)
// {
//     t_vec3  position;
//     t_vec3  direction;
//     float   fov;
    
//     if (count != 4)
//         puts(RED"invalid nbrs for camera"rst), exit(1);
//     position = get_vec3(param[0]); 
//     direction = get_vect3(param[1]);
//     get_float(param[2]);
//     new_camera(position, direction, 1280.0f / 720, fov);
//     return (0);
// }

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	check_line(char *line, t_scene *scene, t_parser* parser)
{
	char **param;
    size_t count;

	while (ft_isspace(*line))
		line++;
	param = ft_split(line, &count);
    if (count == 0)
        puts(RED"empty line"rst);
    if (parser->camera_count == 0 && !strcmp(param[0], "C"))
	{
		puts(GREEN"here is a camera"rst);
        // fill_camera(param, count);
		parser->camera_count = 1;
 	}
	else if (parser->ambient_count != 1 && !strcmp(param[0], "A"))
	{
    	puts(GREEN"here is an ambient light"rst);
        // fill_ambient(param, count);

		parser->ambient_count = 1;
 	}
    else if (parser->light_count == 0 && !strcmp(param[0], "L"))
	{
        puts(GREEN"here is a light"rst);
        // fill_light(param, count);
		parser->light_count = 1;   
 	}
	else
	{
		free_array(param);
		return(1);
	}
	free_array(param);
}


int	read_file(char *file, t_scene *scene, t_parser* parser)
{
	char	*line;
	int		fd;

	line = "";
	fd = open(file, O_RDONLY);
	if (fd < 0)
		puts(RED"file doesn't exist ):"rst), exit(1);
	while (line)
	{
		line = get_next_line(fd);
		if (!line || line[0] == '\n')
			break ;
		if (check_line(line, scene, parser) == ERROR)
			puts(RED"parsing error!"rst), free(line), exit(1);
	free(line);
	}
	if (!parser->ambient_count || !parser->camera_count || !parser->light_count)
		puts(RED"item missed!"rst), free(line), exit(1);
	free(line);
	close(fd);
	return (0);
}

int	check_args(char *s)
{
	char *type;

	type = ".rt";
	if (!f_is_rt_file(s, type))
		return (SUCESS);
	else
	{
		printf(RED"should enter rt file :) \n"rst);
		exit (1);
	}
}
int parsing(t_scene *scene, int ac, char **av, t_parser*parser)
{
	if (ac == 2)
	{
		if (check_args(av[1]) == SUCESS)
			read_file(av[1], scene, parser);
		return (SUCESS);
	}
	else if (ac != 2)
		return (ERROR);
	return (ERROR);
}
