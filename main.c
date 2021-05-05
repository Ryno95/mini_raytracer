/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:28:19 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/05 16:57:18 by rmeiboom      ########   odam.nl         */
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
	t_rgb			**col_array;
	
	printf("argcount: %d\n", argc);
	if (argc < 2 || argc > 3)
	{
		printf("Usage: ./executable scene.rt");
		return (-1);
	}
	// printf("argv[2]: %s\n", argv[2]);
	if (argc == 3 && ft_strncmp(argv[2], "--save", ft_strlen("--save")) == 0)
	{
		env.save_to_bmp = 1;
		env.fd = create_bmp("minirt.bmp");
		if (env.fd < 0)
			ft_parse_error("Not enough mem for bmp");
	}
	if (parse(argv[1], &env) == -1)
		ft_parse_error("");
	
	if (env.save_to_bmp != 1)
		ft_run_mlx(&img, &env);
	
	col_array = ft_render(&img, &env);
	
	if (env.save_to_bmp != 1)
	{
		mlx_put_image_to_window(img.mlx_ptr, img.wdw_ptr, img.img_ptr, 0, 0);
		mlx_hook(img.wdw_ptr, 17, 1l << 17, my_destroy_window, &img);
		mlx_hook(img.wdw_ptr, 2, 1l << 0, keypress, &img);
		mlx_loop(img.mlx_ptr);
	}
	// while (i < TRIANGLE)
	// {
	// 	ft_lstclear(&env.shapes[i], free);
	// 	i++;
	// }
	// printf("campoint: %p\n", env.cam_list->content);
	// mlx_mouse_hook(img.wdw_ptr, ft_debugray, &env);
	if (env.save_to_bmp)
		close(env.fd);
	// ft_lstclear(&env.light, free);
	// ft_lstclear(&env.cam_list, free);
	// if(env.debug)
	// while(1);
	return (0);
}