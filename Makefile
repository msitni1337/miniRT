# SRCS
LinAlgebra	= src/linear_algebra/Mat4x4.c src/linear_algebra/Vec3.c
Renderer	= src/renderer/Camera.c src/renderer/Ray.c src/renderer/Renderer.c src/renderer/Shading.c
Parser_m	= src/parser/ft_split.c src/parser/get_next_line.c src/parser/get_next_line_utils.c src/parser/get_vec3.c src/parser/parser.c src/parser/parser_utils.c 
Parser_b	= src/parser/ft_split.c src/parser/get_next_line.c src/parser/get_next_line_utils.c src/parser/get_vec3.c src/parser/parser_bonus.c src/parser/parser_utils.c 
Object_m	= src/objects/mandatory/Cylinder.c src/objects/mandatory/Light.c src/objects/mandatory/Object.c src/objects/mandatory/Plane.c src/objects/mandatory/Sphere.c
Object_b	= ${Object_m} src/objects/bonus/Cone_bonus.c src/objects/bonus/Cone_cap_bonus.c src/objects/bonus/Rectangle_bonus.c
input		= src/input/camera.c src/input/object.c
utils		= src/utils/dynamic_arrays.c src/utils/free.c src/utils/logging.c src/utils/ft_memset.c src/mlx/mlx_utils.c 

mandatory_src	= src/main.c src/mlx/mlx_init.c src/input/input.c
bonus_src		= src/main_bonus.c src/mlx/mlx_init_bonus.c src/input/input.c
extra_src		= src/main_bonus.c src/mlx/mlx_init_bonus.c src/parser/scene_gen_extra.c src/input/input_extra.c

SRC_m		= ${LinAlgebra} ${Renderer} ${Parser_m} ${Object_m} ${input} ${utils} ${mandatory_src} 
OBJ_m		= $(SRC_m:.c=.o)

SRC_b		= ${LinAlgebra} ${Renderer} ${Parser_b} ${Object_b} ${input} ${utils} ${bonus_src}
OBJ_b		= $(SRC_b:.c=.o)

SRC_e		= ${LinAlgebra} ${Renderer} ${Parser_b} ${Object_b} ${input} ${utils} ${extra_src}
OBJ_e		= $(SRC_e:.c=.o)

# VARS
CC = cc
NAME = miniRT
NAME_b = miniRT_bonus
NAME_e = miniRT_extra
CFLAGS = -Iincludes -Wall -Wextra -Werror -O3
LDFLAGS = -Lmlx_Linux -lmlx_Linux -lXext -lX11 -lm

ifeq ($(shell uname -s),Darwin)
	CFLAGS += -DINPUT_MAC
	LDFLAGS = -L. -lmlx -framework OpenGL -framework AppKit
endif

.PHONY : re reb ree fclean clean all bonus extra
.SECONDARY : ${OBJ_m} ${OBJ_b} ${OBJ_e}

%.o : %.c
	$(CC) $(CFLAGS) $< -c -o $@

all : ${NAME}
bonus: ${NAME_b}
extra: ${NAME_e}

clean :
	rm -f ${OBJ_m} ${OBJ_e}

fclean : clean
	rm -f $(NAME)
	rm -f $(NAME_b)
	rm -f $(NAME_e)

${NAME}: $(OBJ_m)
	$(CC) $(CFLAGS) $(OBJ_m) -o $(NAME) $(LDFLAGS)

${NAME_b}: $(OBJ_b)
	$(CC) $(CFLAGS) $(OBJ_b) -o $(NAME_b) $(LDFLAGS)

${NAME_e}: $(OBJ_e)
	$(CC) $(CFLAGS) $(OBJ_e) -o $(NAME_e) $(LDFLAGS)

re : fclean all
reb : fclean bonus
ree : fclean extra