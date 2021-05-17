/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/17 22:34:38 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

static void	ft_render_loop(t_env *env)
{
	int		y;
	int		x;
	int		i;
	t_rgb	color;

	y = 0;
	while (y < env->res.y)
	{
		x = 0;
		while (x < env->res.x)
		{
			color = ft_tracer(x, y, env);
			if (env->save_to_bmp == 1)
				i = (env->res.y - y - 1) * env->res.x + x;
			else
				i = y * env->res.x + x;
			ft_assign_t3rgb(color, &env->col_array[i]);
			x++;
		}
		y++;
	}
}

int	ft_render(t_env *env)
{
	env->col_array = (t_3rgb *)malloc(env->res.y * env->res.x * sizeof(t_3rgb));
	if (!env->col_array)
		ft_parse_error("Not enough memory for color array");
	ft_render_loop(env);
	return (1);
}
