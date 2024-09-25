#ifndef PARSER_BONUS_H
#define PARSER_BONUS_H
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "dynamic_arrays.h"
#include "Renderer.h"
#include "utils.h"


#define BUFFER_SIZE 42
#define rst   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define SUCESS	0
#define ERROR	1

typedef struct s_parser
{
	int camera_count;
	int ambient_count;
	t_darr objects;
	t_darr lights;
} t_parser;

char *get_next_line(int fd);
int parsing(t_scene *scene, int ac, char **av);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
int ft_isspace(char c);
char **ft_split(char const *s, size_t *count, int (*delim)(char));
size_t ft_strlen(const char *s);
int get_vec3(t_vec3*vec3, char*str);
int get_float(float*f, char*str);
int is_valid_color(t_vec3 color);
int is_normalized(t_vec3 vec);

#endif