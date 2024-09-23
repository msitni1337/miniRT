# SRCS
SRC = $(wildcard src/*/*.c) $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

# VARS
CC = cc
NAME = miniRT
CFLAGS = -O3 -Iincludes -g3 -fsanitize=address
LDFLAGS = -Lmlx_Linux -lmlx_Linux -lXext -lX11 -lm


.PHONY : re fclean clean all bonus
.SECONDARY : ${OBJ}

all : mandatory

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

mandatory: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) tests/main.c -o $(NAME) $(LDFLAGS)

basic_rendering: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) tests/Basic_rendering.c -o $(NAME) $(LDFLAGS)

re : fclean all
