CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME = minirt

# HEADER = minirt.h
LIBS = libft/libft.a

OBJ = main.o\
	gnl/get_next_line.o\
	gnl/get_next_line_utils.o\
	parse/parse.o\
	parse/parse_env.o\
	parse/parse_shapes.o\
	window_control/ft_window.o\
	utils/ft_free.o\
	utils/ft_parse_utils.o\
	utils/ft_errors.o\
	utils/draw_utils.o\
	utils/vec_products.o\
	utils/vec_utils.o\
	tracer/draw_shapes.o\
	tracer/ft_render.o\
	tracer/ft_sphere_intersection.o

all: $(NAME)

# Move the dynamic lib to root dir and compile
$(NAME): $(OBJ)
		cd mlx && $(MAKE)
		cd libft && $(MAKE)
		$(CC) $(CFLAGS) $(OBJ) $(LIBS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
		$(CC) -c -Wall -Wextra -o $@ $<

clean: 
		rm -f $(OBJ) libft/*.o

fclean: clean
		rm -f $(NAME) libft/libft.a

re: fclean all

.PHONY: all clean fclean re