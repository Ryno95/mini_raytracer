/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_color_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 13:46:56 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/30 18:09:27 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_structure.h"

int	ft_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_color_check(t_rgb *col)
{
	if (col->r > 255)
		col->r = 255;
	else if (col->r < 0.0001)
		col->r = 0;
	if (col->g > 255)
		col->g = 255;
	else if (col->g < 0.0001)
		col->g = 0;
	if (col->b > 255)
		col->b = 255;
	else if (col->b < 0.0001)
		col->b = 0;
}

void	ft_color_multi(t_rgb *col, double factor)
{
	col->r *= factor;
	col->g *= factor;
	col->b *= factor;
	ft_color_check(col);
}

t_rgb	ft_colors_add(t_rgb col, t_rgb rgb)
{
	col.r += rgb.r;
	col.g += rgb.g;
	col.b += rgb.b;
	ft_color_check(&col);
	return (col);
}

t_rgb	ft_color_times_color(t_rgb col, t_rgb factor)
{
	col.r = (col.r * factor.r) / 255;
	col.g = (col.g * factor.g) / 255;
	col.b = (col.b * factor.b) / 255;
	return (col);
}
