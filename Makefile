# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rmeiboom <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/15 16:56:30 by rmeiboom      #+#    #+#                  #
#    Updated: 2021/05/15 17:49:35 by rmeiboom      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror  -Wextra  -g -fsanitize=address
NAME = minirt
LIBS = libft/libft.a
LIBFTDIR = libft/
MLXDIR = mlx/
GNLDIR = gnl/
MAN_MAIN = main.o

OBJ = gnl/get_next_line.o\
	gnl/get_next_line_utils.o\
	parse/parse.o\
	parse/parse_env.o\
	parse/parse_shapes.o\
	utils/ft_free.o\
	utils/ft_parse_utils.o\
	utils/ft_errors.o\
	utils/ft_draw_utils.o\
	utils/ft_vec_products.o\
	utils/ft_vec_basic_math.o\
	utils/ft_vec_create.o\
	utils/ft_color_utils.o\
	utils/ft_matrices.o\
	utils/ft_filters.o\
	rendering/ft_render.o\
	rendering/ft_tracing.o\
	rendering/ft_sphere_intersection.o\
	rendering/ft_plane_intersect.o\
	rendering/ft_shadowing.o\
	rendering/ft_triangle_intersection.o\
	rendering/ft_square_intersect.o\
	rendering/ft_cylinder_intersect.o\
	output/ft_output_to_bmp.o\
	output/ft_window.o\

BONUS_OBJ = bonus/main_bonus.o\
		bonus/ft_multithreading.o

ifdef WITH_BONUS
O_FILES = $(BONUS_OBJ) $(OBJ)
else
O_FILES = $(OBJ) $(MAN_MAIN)
endif

all: $(NAME)

$(NAME): $(O_FILES)
		make -C $(LIBFTDIR)
		make -C $(MLXDIR)		
		$(CC) $(CFLAGS) $(O_FILES) $(LIBS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
		$(CC) -c $(CFLAGS) -o $@ $<

bonus:
	$(MAKE) WITH_BONUS=1 all

clean: 
		rm -f $(OBJ) $(MAN_MAIN) $(BONUS_OBJ)
		rm -f minirt.bmp

fclean: clean
		rm -f $(NAME)
		make -C $(LIBFTDIR) fclean
		make -C $(MLXDIR) clean

re: fclean all

.PHONY: all clean fclean re bonus
