/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:28:19 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/30 18:01:54 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minirt.h"
#include "mlx/mlx.h"
#include <fcntl.h>
// #include "ft_structure.h"

void	ft_mlx_error(char *str)
{
	printf("Error!\n%s\n", str);
	exit(1);
}

int	main(int argc, char *argv[])
{
	static	t_env	env;
	t_img			img;
	
	if (argc != 2)
	{
		printf("Usage: ./executable scene.rt");
		return (-1);
	}
	if (parse(argv[1], &env) == -1)
		ft_parse_error("");
	
	ft_run_mlx(&img, &env);
	
	// while (i < TRIANGLE)
	// {
	// 	ft_lstclear(&env.shapes[i], free);
	// 	i++;
	// }
	// printf("campoint: %p\n", env.cam_list->content);
	// mlx_mouse_hook(img.wdw_ptr, ft_debugray, &env);
	mlx_hook(img.wdw_ptr, 17, 1l << 17, my_destroy_window, &img);
	mlx_hook(img.wdw_ptr, 2, 1l << 0, keypress, &img);
	mlx_loop(img.mlx_ptr);
	// ft_lstclear(&env.light, free);
	// ft_lstclear(&env.cam_list, free);
	// if(env.debug)
	// while(1);
	return (0);
}