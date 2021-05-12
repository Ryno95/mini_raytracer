/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 18:22:02 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/12 18:27:26 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include "../headers/ft_structure.h"

void ft_exit(t_env *env, char *description)
{
	int i;

	i = 0;
	while (i < CYLINDER)
	{
		ft_lstclear(env->shapes[i], free);
		i++;
	}
	ft_lstclear(env->light, free);
	ft_lstclear(env->cam_list, free);
	if (env->col_array)
		free(env->col_array);
	printf("Error: %s\n", description);
	exit(1);
}

void	free_split(char **split_array)
{
	int	i;

	if (!split_array)
		return ;
	i = 0;
	while (split_array[i])
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
}
