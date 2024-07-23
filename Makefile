# SRCS
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

# VARS
CC = cc
NAME = miniRT
CFLAGS = -Iincludes -g3 #-Wall -Werror -Wextra # -g3 -fsanitize=address
LDFLAGS = -Lmlx_linux -lmlx -lXext -lX11 -lm


.PHONY : re fclean clean all bonus
.SECONDARY : ${OBJ}

all : $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
