CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME = scene.rt

# HEADER = minirt.h

OBJ = main.o

all: $(NAME)

# Move the dynamic lib to root dir and compile
$(NAME): $(OBJ)
		cd mlx && $(MAKE)
		$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
		$(CC) -c -o $@ $<

clean: 
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re