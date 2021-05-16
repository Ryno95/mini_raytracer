/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_draw_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 22:26:53 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/16 16:01:38 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

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
