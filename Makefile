# SRCS
LinAlgebra	= src/linear_algebra/Mat4x4.c src/linear_algebra/Vec3.c
Renderer	= src/renderer/Camera.c src/renderer/Ray.c src/renderer/Renderer.c
Parser_m	= src/parser/ft_split.c src/parser/get_next_line.c src/parser/get_vec3.c src/parser/parser.c src/parser/parser_utils.c 
Parser_b	= src/parser/ft_split.c src/parser/get_next_line.c src/parser/get_vec3.c src/parser/parser_bonus.c src/parser/parser_utils.c 
Object_m	= src/objects/mandatory/Cylinder.c src/objects/mandatory/Light.c src/objects/mandatory/Object.c src/objects/mandatory/Plane.c src/objects/mandatory/Sphere.c
Object_b	= ${Object_m} src/objects/bonus/Cone_bonus.c src/objects/bonus/Cone_cap_bonus.c src/objects/bonus/Rectangle_bonus.c
input		= src/input/input.c
utils		= src/utils/dynamic_arrays.c src/utils/free.c src/utils/logging.c src/utils/mlx_utils.c

SRC_m = ${LinAlgebra} ${Renderer} ${Parser_m} ${Object_m} ${input} ${utils} tests/main.c
OBJ_m = $(SRC_m:.c=.o)

SRC_b = ${LinAlgebra} ${Renderer} ${Parser_b} ${Object_b} ${input} ${utils} tests/main_bonus.c
OBJ_b = $(SRC_b:.c=.o)

# VARS
CC = cc
NAME = miniRT
NAME_b = miniRT_bonus
CFLAGS = -O3 -Iincludes -g3 -fsanitize=address
LDFLAGS = -Lmlx_Linux -lmlx_Linux -lXext -lX11 -lm

ifeq ($(shell uname -s),Darwin)
	CFLAGS += -DINPUT_MAC
	LDFLAGS = -L. -lmlx -framework OpenGL -framework AppKit
endif

.PHONY : re fclean clean all bonus
.SECONDARY : ${OBJ_m} ${OBJ_b}

%.o : %.c
	$(CC) $(CFLAGS) $< -c -o $@

all : ${NAME}
bonus: ${NAME_b}

clean :
	rm -f ${OBJ_m} ${OBJ_b}

fclean : clean
	rm -f $(NAME)
	rm -f $(NAME_b)

${NAME}: $(OBJ_m)
	$(CC) $(CFLAGS) $(OBJ_m) -o $(NAME) $(LDFLAGS)

 ${NAME_b}: $(OBJ_b)
	$(CC) $(CFLAGS) $(OBJ_b) -o $(NAME_b) $(LDFLAGS)

re : fclean all
