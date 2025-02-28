SRC	=	src/main.c

OBJ     =       $(SRC:.cpp=.o)

NAME    =      Snake

all:    $(NAME)

CFLAGS = -Wall -Werror -Wextra -lcsfml-graphics -lcsfml-window -lcsfml-system

$(NAME):        $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean

re:     fclean all

.PHONY: all clean fclean