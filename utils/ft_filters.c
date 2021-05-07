/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_filters.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/07 10:37:15 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/07 15:49:42 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
// grayscale = (r + b + c)  / 3;
t_3rgb 	*ft_grayscale(t_3rgb *colors, int width, int height)
{
	int	grayscaled;
	int	i;
	int	size;

	i = 0;
	size = width * height;
	while (i < size)
	{
		grayscaled = (colors[i].r + colors[i].g + colors[i].b) / 3;
		colors[i].r = grayscaled; 
		colors[i].g = grayscaled;
		colors[i].b = grayscaled;
		i++;
	}
	return (colors);
}

t_3rgb	*ft_sepia(t_3rgb *col, int width, int height)
{
	t_3rgb sepia[height * width];
	int i;
	int size;

	i = 0;
	size = width * height;
	while (i < size)
	{
		sepia[i].r = 255;
		if ((col[i].r * 0.393 + col[i].g * 0.769 + col[i].b * 0.189) <= 255)
			sepia[i].r = col[i].r * 0.393 + col[i].g * 0.769 + col[i].b * 0.189;
		sepia[i].g = 255;
		if ((col[i].r * 0.349 + col[i].g * 0.686 + col[i].b * 0.168) <= 255)
			sepia[i].g = col[i].r * 0.349 + col[i].g * 0.686 + col[i].b * 0.168;
		sepia[i].b = 255;
		if ((col[i].r * 0.272 + col[i].g * 0.534 + col[i].b * 0.131) <= 255)
			sepia[i].b = col[i].r * 0.272 + col[i].g * 0.534 + col[i].b * 0.131;
		i++;
	}
	col = &sepia[0];
	return (col);
}
