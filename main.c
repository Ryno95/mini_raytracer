/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:28:19 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/07 20:35:59 by rmeiboom      ########   odam.nl         */
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

void	ft_put_img_to_window(t_img *img, t_env *env, t_3rgb *cols)
{
	int i;
	int j;
	int pos;
	int color;

	if (env->filters.sepia)
		cols = ft_sepia(cols, env->res.x, env->res.y);
	else if (env->filters.grayscale)
		cols = ft_grayscale(cols, env->res.x, env->res.y);
	i = 0;
	while (i < env->res.y)
	{
		j = 0;
		while (j < env->res.x)
		{
			pos = i * env->res.x + j;
			color = ft_create_trgb(0, cols[pos].r, cols[pos].g, cols[pos].b);
			my_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->wdw_ptr, img->img_ptr, 0, 0);
}

void	ft_check_args(int argc, char *argv[], t_env * env)
{
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", ft_strlen("--save")) == 0)
			env->save_to_bmp = 1;
		else if (ft_strncmp(argv[2], "-s", 2) == 0)
			env->filters.sepia = 1;
		else if (ft_strncmp(argv[2], "-g", 2) == 0)
			env->filters.grayscale = 1;
		else
			ft_parse_error("Usage: ./executable scene.rt [--save] [-filter:s/g]");
	}
	else if (argc == 4 && ft_strncmp(argv[2], "--save", ft_strlen("--save")) == 0)
	{
		env->save_to_bmp = 1;
		if (ft_strncmp(argv[3], "-s", 2) == 0)
			env->filters.sepia = 1;
		else if (ft_strncmp(argv[3], "-g", 2) == 0)
			env->filters.grayscale = 1;
		else
			ft_parse_error("Usage: ./executable scene.rt [--save] [-filter:s/g]");
	}
	else
		ft_parse_error("Usage: ./executable scene.rt [--save] [-filter:s/g]");
}


int	main(int argc, char *argv[])
{
	static	t_env	env;
	t_img			img;
	
	printf("argc:%d\n", argc);
	if (argc < 2 || argc > 4)
		ft_parse_error("Usage: ./executable scene.rt [--save] [-filter:s/g]");
	if (argc == 3 || argc == 4)
		ft_check_args(argc, argv, &env);
		
	if (parse(argv[1], &env) == -1)
		ft_parse_error("");
		
	if (env.save_to_bmp != 1)
		ft_run_mlx(&img, &env);
		
	if(ft_render(&env) != 1)
		ft_parse_error("Rendering failed");
	printf("here!\n\n\n");
	if (env.save_to_bmp == 1)
	{
		ft_put_img_to_bmp("minirt.bmp", &env, env.col_array);
		close(env.fd);
		// free(col_array);
	}
	else
	{
		ft_put_img_to_window(&img, &env, env.col_array);
		mlx_hook(img.wdw_ptr, 17, 1l << 17, my_destroy_window, &img);
		mlx_hook(img.wdw_ptr, 2, 1l << 0, keypress, &img);
		mlx_loop_hook(img.mlx_ptr, ft_render, &env);
		mlx_loop(img.mlx_ptr);
	}
	// while (i < TRIANGLE)
	// {
	// 	ft_lstclear(&env.shapes[i], free);
	// 	i++;
	// }
	// printf("campoint: %p\n", env.cam_list->content);
	// mlx_mouse_hook(img.wdw_ptr, ft_debugray, &env);

	// ft_lstclear(&env.light, free);
	// ft_lstclear(&env.cam_list, free);
	// if(env.debug)
	// while(1);
	return (0);
}