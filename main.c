/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:28:19 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/19 10:39:06 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minirt.h"
#include "mlx/mlx.h"
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>

void	ft_mlx_error(char *str)
{
	printf("Error!\n%s\n", str);
	exit(1);
}

void	ft_switch_camera(t_img *img)
{
	if (img->env->cam_list->next)
		img->env->cam_list = img->env->cam_list->next;
	ft_render(img->env);
	ft_put_img_to_window(img, img->env, img->env->col_array);
	return ;
}

void	ft_check_args(int argc, char *argv[], t_env *env)
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
			ft_parse_error(USAGE);
	}
	else if (argc == 4 && ft_strncmp(argv[2], \
		"--save", ft_strlen("--save")) == 0)
	{
		env->save_to_bmp = 1;
		if (ft_strncmp(argv[3], "-s", 2) == 0)
			env->filters.sepia = 1;
		else if (ft_strncmp(argv[3], "-g", 2) == 0)
			env->filters.grayscale = 1;
		else
			ft_parse_error(USAGE);
	}
	else
		ft_parse_error(USAGE);
}

void	ft_protection_checks(int argc, char *argv[], t_env *env)
{
	if (argc < 2 || argc > 4)
		ft_parse_error(USAGE);
	if (argc == 3 || argc == 4)
		ft_check_args(argc, argv, env);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 3], FILE_EXTENSION, 4) != 0)
		ft_parse_error(USAGE);
	if (parse(argv[1], env) == -1)
		ft_parse_error("");
}

int	main(int argc, char *argv[])
{
	static t_env	env;

	ft_protection_checks(argc, argv, &env);
	env.col_array = (t_3rgb *)malloc(env.res.y * env.res.x * sizeof(t_3rgb));
	if (!env.col_array)
		ft_parse_error("Couldn't allocate mem to parse");
	ft_check_screen_size(&env);
	if (ft_render(&env) != 1)
		ft_parse_error("Rendering failed");
	if (env.save_to_bmp == 1)
	{
		if (!ft_put_img_to_bmp("minirt.bmp", &env, env.col_array))
			ft_exit(&env, "Output to bmp failed");
		close(env.fd);
		ft_exit(&env, "Succesful output to .bmp");
	}
	else if (!ft_run_mlx(&env))
		ft_exit(&env, "Error displaying image");
	return (0);
}
