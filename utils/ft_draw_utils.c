/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_draw_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 22:26:53 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/19 10:41:14 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include "../mlx/mlx.h"
#include <stdio.h>

void	my_pixel_put(t_img *img, int x, int y, unsigned int colour)
{
	char	*dst;
	int		offset;

	offset = y * img->line_size + x * (img->bits_per_pixel / 8);
	dst = img->address + offset;
	*(unsigned int *)dst = colour;
}

void	ft_assign_t3rgb(t_rgb big_col, t_3rgb *small_col)
{
	small_col->r = (uint8_t)big_col.r;
	small_col->g = (uint8_t)big_col.g;
	small_col->b = (uint8_t)big_col.b;
}

void	ft_check_screen_size(t_env *env)
{
	int	max_width;
	int	max_height;

	max_width = 0;
	max_height = 0;
	env->mlx_ptr = mlx_init();
	if (!env->mlx_ptr)
		ft_mlx_error("Couldn't init mlx");
	mlx_get_screen_size(env->mlx_ptr, &max_width, &max_height);
	if (env->res.x > max_width && env->save_to_bmp != 1)
	{
		env->res.x = max_width;
		printf("Resizing screen width to: %d\n", max_width);
	}
	if (env->res.y > max_height && env->save_to_bmp != 1)
	{
		env->res.y = max_height;
		printf("Resizing screen height to: %d\n", max_height);
	}	
}
