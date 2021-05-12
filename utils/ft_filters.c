/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_filters.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/07 10:37:15 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/12 18:52:19 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

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
	t_3rgb	*sep;
	int		i;
	int		size;

	sep = (t_3rgb *)malloc(height * width * sizeof(t_3rgb));
	ft_memcpy(sep, col, height * width * sizeof(t_3rgb));
	i = 0;
	size = width * height;
	while (i < size)
	{
		col[i].r = 255;
		if ((sep[i].r * 0.393 + sep[i].g * 0.769 + sep[i].b * 0.189) <= 255)
			col[i].r = sep[i].r * 0.393 + sep[i].g * 0.769 + sep[i].b * 0.189;
		col[i].g = 255;
		if ((sep[i].r * 0.349 + sep[i].g * 0.686 + sep[i].b * 0.168) <= 255)
			col[i].g = sep[i].r * 0.349 + sep[i].g * 0.686 + sep[i].b * 0.168;
		col[i].b = 255;
		if ((sep[i].r * 0.272 + sep[i].g * 0.534 + sep[i].b * 0.131) <= 255)
			col[i].b = sep[i].r * 0.272 + sep[i].g * 0.534 + sep[i].b * 0.131;
		i++;
	}
	free(sep);
	return (col);
}
