/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_multithreading.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/15 13:59:47 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 17:02:29 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <pthread.h>

void	*ft_thread_render(void *thread_data)
{
	int			i;
	int			j;
	int			k;
	t_rgb		color;
	t_thread	*thread;

	thread = (t_thread *)thread_data;
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
	int			i;
	t_thread	threads[NUMBER_OF_THREADS];

	i = 0;
	while (i < NUMBER_OF_THREADS)
	{
		threads[i].env = env;
		threads[i].id = i;
		if (pthread_create(&threads[i].tid, NULL, ft_thread_render,\
			(void *)&threads[i]) != 0)
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