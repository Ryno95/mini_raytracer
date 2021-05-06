/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:28:19 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/06 21:31:10 by rmeiboom      ########   odam.nl         */
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

void	ft_write_to_window(t_img *img, int height, int width, t_rgb **cols)
{
	int i;
	int j;
	int color;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			color = ft_create_trgb(0, cols[i][j].r, cols[i][j].g, cols[i][j].b);
			my_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->wdw_ptr, img->img_ptr, 0, 0);
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
	if (argc == 3 && ft_strncmp(argv[2], "--save", ft_strlen("--save")) == 0)
		env.save_to_bmp = 1;

	if (parse(argv[1], &env) == -1)
		ft_parse_error("");
	
	if (env.save_to_bmp != 1)
		ft_run_mlx(&img, &env);
	
	col_array = ft_render(&env);
	// printf("red:%f\n", col_array[10][10].r);
	
	if (env.save_to_bmp == 1)
		ft_put_img_to_bmp("minirt.bmp", env.res.y, env.res.x, col_array);
	else
	{
		ft_write_to_window(&img, env.res.y, env.res.x, col_array);
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
	free(col_array);
	// ft_lstclear(&env.light, free);
	// ft_lstclear(&env.cam_list, free);
	// if(env.debug)
	// while(1);
	return (0);
}