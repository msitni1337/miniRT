#ifndef PARSER_H
#define PARSER_H
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "Renderer.h"


# define BUFFER_SIZE 42

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
	int light_count;
	int pl_count;
	int sp_count;
	int cy_count;
} t_parser;

int parsing(t_scene *scene, int ac, char **av, t_parser*parser);
int ft_isspace(char c);
char **ft_split(char const *s, size_t *count, int (*delim)(char));
size_t ft_strlen(const char *s);

#endif