#ifndef MLX_UTILS_H
#define MLX_UTILS_H
typedef struct s_img
{
	void *handle;
	char *data;
	int bpp;
	int size_line;
	int width;
	int height;
	int endian;
} t_img;

#endif // MLX_UTILS_H