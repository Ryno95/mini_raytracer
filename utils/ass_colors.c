/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ass_colors.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/05 17:03:23 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/05 20:36:44 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	ass_colors(char *str, t_rgb *cols)
{
	char **sl;
	
	sl = ft_split(str, ',');
	if (!sl || !cols)
		return ;
	if (ft_atoi(sl[0]) > 0)
		cols->r = ft_atoi(sl[0]);
	if (ft_atoi(sl[1]) > 0)
		cols->g = ft_atoi(sl[1]);
	if (ft_atoi(sl[2]) > 0)
		cols->b = ft_atoi(sl[2]);
	free_split(sl);
}

void	ass_coords(char *str, t_coord *coords)
{
	char **sl;
	
	sl = ft_split(str, ',');
	if (!sl || !coords)
		return ;
	if (ft_atof(sl[0]) > 0)
		coords->x = ft_atof(sl[0]);
	if (ft_atof(sl[1]) > 0)
		coords->y = ft_atof(sl[1]);
	if (ft_atof(sl[2]) > 0)
		coords->z = ft_atof(sl[2]);
	free_split(sl);
}

float	ft_vec_len(t_coord coords)
{
	return(sqrt(pow((coords.x), 2) + pow((coords.y), 2) + pow((coords.z), 2)));	
}