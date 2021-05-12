/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:28:19 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/12 19:12:24 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minirt.h"
#include "mlx/mlx.h"
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>

#define NUMBER_OF_THREADS 4
// #include "ft_structure.h"

void	ft_mlx_error(char *str)
{
	printf("Error!\n%s\n", str);
	exit(1);
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


void *ft_thread_render(void *thread_data)
{
	int		i;
	int		j;
	int		k;
	t_rgb	color;
	t_thread *thread = (t_thread *)thread_data; 

	i = thread->id;
	while (i < thread->env->res.y)
	{
		j = 0;
		while (j < thread->env->res.x)
		{
			color = ft_tracer(j, i, thread->env);
			if (thread->env->save_to_bmp == 1)
				k = (thread->env->res.y - i - 1) * thread->env->res.x + j;
			else
				k = i * thread->env->res.x + j;
			thread->env->col_array[k].r = (uint8_t)color.r;
			thread->env->col_array[k].g = (uint8_t)color.g;
			thread->env->col_array[k].b = (uint8_t)color.b;
			j++;
		}
		i += NUMBER_OF_THREADS;
	}
	return (NULL);
}

void	ft_threading_render(t_env *env)
{
	int i;
	t_thread		threads[NUMBER_OF_THREADS];

	i = 0;
	while (i < NUMBER_OF_THREADS)
	{
		threads[i].env = env;
		threads[i].id = i;
		if(pthread_create(&threads[i].tid, NULL, ft_thread_render, (void*)&threads[i]) != 0)
			ft_parse_error("Threading error");
		i++;
	}
	i = 0;
	while (i < NUMBER_OF_THREADS)
	{
		pthread_join(threads[i].tid, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	static	t_env	env;
	
	
	printf("argc:%d\n", argc);
	if (argc < 2 || argc > 4)
		ft_parse_error("Usage: ./executable scene.rt [--save] [-filter:s/g]");
	if (argc == 3 || argc == 4)
		ft_check_args(argc, argv, &env);
		
	if (parse(argv[1], &env) == -1)
		ft_parse_error("");
	
	env.col_array = (t_3rgb *)malloc(env.res.y * env.res.x * sizeof(t_3rgb));
	if (!env.col_array)
		ft_parse_error("You fucked up!");

	ft_threading_render(&env);
	
	// if(ft_render(&env) != 1)
	// 	ft_parse_error("Rendering failed");
	
	if (env.save_to_bmp == 1)
	{
		ft_put_img_to_bmp("minirt.bmp", &env, env.col_array);
		close(env.fd);
		free(env.col_array);
	}
	else
		if(!ft_run_mlx(&env))
			ft_exit(&env, "Error displaying image");

	// while(1);
	return (0);
}