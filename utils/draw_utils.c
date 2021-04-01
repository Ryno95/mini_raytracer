/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 22:26:53 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/01 20:49:21 by rmeiboom      ########   odam.nl         */
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

void	my_lstiter(t_list *lst, t_img *img, void (*f)(t_img *, void *))
{
	if (!f)
		return ;
	while (lst != NULL)
	{
		f(img, lst->content);
		lst = lst->next;
	}
}