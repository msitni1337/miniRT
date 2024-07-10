# SRCS
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# VARS
CC = cc
NAME = miniRT
CFLAGS = -Wall -Werror -Wextra -Iincludes # -g3 -fsanitize=address
LDFLAGS = -lm


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