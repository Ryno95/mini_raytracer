CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME = minirt

# HEADER = minirt.h
# LIBS = libft/libft.a

OBJ = main.o\
	# gnl/get_next_line.o\
	# gnl/get_next_line_utils.o\
	# parse/parse.o\
	# parse/parse_env.o\
	# parse/parse_shapes.o\
	# utils/ft_free.o\
	# utils/ft_parse_utils.o\
	# utils/ft_errors.o\
	# utils/ft_math_utils.o

all: $(NAME)

# Move the dynamic lib to root dir and compile
$(NAME): $(OBJ)
		cd mlx && $(MAKE)
		# cd libft && $(MAKE)
		$(CC) $(CFLAGS) $(OBJ) $(LIBS)  -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
		$(CC) -c -o $@ $<

clean: 
		rm -f $(OBJ) libft/*.o

fclean: clean
		rm -f $(NAME) libft/libft.a

re: fclean all

.PHONY: all clean fclean re