/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 22:26:53 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/10 21:48:10 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	my_pixel_put(t_img *img, int x, int y, unsigned int colour)
{
	char	*dst;
	int		offset;

	// offset traverses the correct amount of memory to the stop in the 
	// img memory where you want to start writing pixel
	offset = y * img->line_size + x * (img->bits_per_pixel / 8);
	// printf("offset: %d\n", offset);
	dst = img->address + offset;
	*(unsigned int *)dst = colour;
}

void	my_lstiter(t_list *lst, t_ray *ray, unsigned int *nearest ,void (*f)(t_list *, t_ray * ,void *))
{
	if (!f)
		return ;
	while (lst != NULL)
	{
		f(lst->content, ray, nearest);
		lst = lst->next;
	}
}

void	color_check(t_rgb *col)
{
	if (col->r > 255)
		col->r = 255;
	else if (col->r < 0)
		col->r = 0;

	if (col->g > 255)
		col->g = 255;
	else if (col->g < 0)
		col->g = 0;

	if (col->b > 255)
		col->b = 255;
	else if (col->b < 0)
		col->b = 0;
}

void	color_multi(t_rgb *col, float factor)
{
	col->r *= factor;
	col->g *= factor;
	col->b *= factor;
}

t_rgb	colors_add(t_rgb col, t_rgb rgb)
{
	col.r += rgb.r;
	col.g += rgb.g;
	col.b += rgb.b;
	
	color_check(&col);
	return (col);
}

t_rgb	color_times_color(t_rgb col, t_rgb factor)
{

	col.r = (col.r * factor.r) / 255;
	col.g = (col.g * factor.g) / 255;
	col.b = (col.b * factor.b) / 255;

	return (col);
}
