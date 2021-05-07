CC = gcc

CFLAGS = -Wall  -Wextra  -g -fsanitize=address # remember to add -werror

NAME = minirt

# HEADER = minirt.h
LIBS = libft/libft.a

LIBFTDIR = libft/

MLXDIR = mlx/

GNLDIR = gnl/

OBJ = Debug/debugray.o\
	main.o\
	gnl/get_next_line.o\
	gnl/get_next_line_utils.o\
	parse/parse.o\
	parse/parse_env.o\
	parse/parse_shapes.o\
	utils/ft_free.o\
	utils/ft_parse_utils.o\
	utils/ft_errors.o\
	utils/draw_utils.o\
	utils/vec_products.o\
	utils/vec_utils.o\
	utils/ft_color_utils.o\
	utils/ft_matrices.o\
	utils/ft_filters.o\
	rendering/ft_render.o\
	rendering/ft_sphere_intersection.o\
	rendering/ft_plane_intersect.o\
	rendering/ft_shadowing.o\
	rendering/ft_triangle_intersection.o\
	rendering/ft_square_intersect.o\
	rendering/ft_cylinder_intersect.o\
	output/ft_output_to_bmp.o\
	output/ft_window.o\

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFTDIR)
		make -C $(MLXDIR)		
		$(CC) $(CFLAGS) $(OBJ) $(LIBS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
		$(CC) -c $(CFLAGS) -o $@ $<

clean: 
		rm -f $(OBJ)
		rm -f minirt.bmp

fclean: clean
		rm -f $(NAME)
		make -C $(LIBFTDIR) fclean
		make -C $(MLXDIR) clean

re: fclean all

.PHONY: all clean fclean re
