/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_shapes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 22:27:05 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/11 22:27:47 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minirt.h"

void ft_draw_square(t_img *img, t_square *sqr)
{
	int i;
	int j;

	i = sqr->coords.y - (sqr->side_size / 2);
	printf("Drawing a square\n");
	// while i >= smallest y coord && i <= biggest y coord
	while (i <= (sqr->coords.y + (sqr->side_size / 2)))
	{
		j = sqr->coords.x - (sqr->side_size / 2);
		if (i < 0 || j < 0)
			break ;
		// while j >= smallest x coord &&  j <= biggest x coord
		while (j <= (sqr->coords.x + (sqr->side_size / 2)))
		{
			my_pixel_put(img, j, i, 0x00ffffff);
			j++;
		}
		i++;
	}
}