/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:28:19 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/02 17:56:50 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>
// #include "ft_structure.h"

// bit shifting = (red * pow(256, ((bits/8) - 1))) + (green * pow(256, ((bits/8) - 1))) + (blue * pow(256, ((bits/8) - 1)));

void	ft_mlx_error(char *str)
{
	printf("Error!\n%s\n", str);
	exit(1);
}

// TODO:
	// draw shapes functions and list
	// check if rounding is necessary 
	// if Yes: ROUND FLOAT 2
int	main(int argc, char *argv[])
{
	int		i = 0;
	// float fuck;
	static	t_env	env;
	t_img			img;
	
	if (argc != 2)
	{
		printf("Usage: ./executable scene.rt");
		return (-1);
	}
	if (parse(argv[1], &env) == -1)
		ft_parse_error("");
	// while (env.shapes[SPHERE]!= NULL)
	// {
	// 	fuck = ((t_sphere*)(env.shapes[SPHERE]->content))->coords.x;
	// 	printf("SPHERE: %f\n", fuck);
	// 	env.shapes[SPHERE] = env.shapes[SPHERE]->next;
	// }
	// ((t_camera *)(scene->camera->content))->pos.x
	
	ft_run_mlx(&img, &env);
	// ft_render(&img, &env);
	// printf("%u\n", create_trgb(0,255, 0 ,0));
	// printf("%u\n", ((t_square*)(env.shapes[SQUARE]->content))->colors.rgb);
	
	ft_lstclear(&env.light, free);
	ft_lstclear(&env.cam_list, free);
	while (i < TRIANGLE)
	{
		ft_lstclear(&env.shapes[i], free);
		i++;
	}
	mlx_hook(img.wdw_ptr, 17, 1l << 17, my_destroy_window, &img);
	mlx_hook(img.wdw_ptr, 2, 1l << 0, keypress, &img);
	mlx_loop(img.mlx_ptr);
	// while(1);
	return (0);
}