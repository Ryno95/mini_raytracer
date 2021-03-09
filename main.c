/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:28:19 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/09 20:59:30 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>

// bit shifting = (red * pow(256, ((bits/8) - 1))) + (green * pow(256, ((bits/8) - 1))) + (blue * pow(256, ((bits/8) - 1)));
unsigned int	create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

// Different components or objects to the project
		// Parsing
		// Error management
		// Drawing shapes from structs
			// Functions for every shape, start KISS!
		// Raytracing calculations
		// Writing to the window or to a .bmp
void	ft_mlx_error(char *str)
{
	printf("Error!\n%s\n", str);
	exit(1);
}


int ft_run_mlx(t_img *img, t_env *env)
{
	int i;
	img->mlx_ptr = mlx_init();
	if (!img->mlx_ptr)
		ft_mlx_error("Couldn't init mlx");
		
	img->wdw_ptr = mlx_new_window(img->mlx_ptr, env->res.x, env->res.y, "TESTIIEES!");
	if (!img->wdw_ptr)
		ft_mlx_error("Couldn't init window");
	
	// get_shape();
		// draw_shapes();
			// While i < triangle && i < camera
				// if id == shape
					// draw_specific_shape

	return (0);
}

// TODO ERROR MANAGEMENT:
	// VECT_COORDS
	// SPLIT LENGTH
	// ROUND FLOAT 2
int	main(int argc, char *argv[])
{
	int		i = 0;
	static	t_env	env;
	// t_img			img;

	if (argc != 2)
	{
		printf("Usage: ./executable scene.rt");
		return (-1);
	}
	if (parse(argv[1], &env) == -1)
		ft_parse_error("");
		
	// ft_run_mlx(&img, &env);
	
	ft_lstclear(&env.light, free);
	ft_lstclear(&env.cam_list, free);
	while (i < TRIANGLE)
	{
		ft_lstclear(&env.shapes[i], free);
		i++;
	}
	// mlx_loop(img.mlx_ptr);
	// while(1);
	return (0);
}