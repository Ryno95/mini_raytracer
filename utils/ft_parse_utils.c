/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parse_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/05 17:03:23 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/30 18:09:11 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	ft_str_arr_len(char **str_array)
{
	int	i;

	i = 0;
	while (str_array && str_array[i] != NULL)
		i++;
	return (i);
}

void	ass_colors(char *str, t_rgb *cols)
{
	char	**sl;

	sl = ft_split(str, ',');
	if (!sl || !cols || ft_str_arr_len(sl) != 3)
		ft_parse_error("colors, safety checks");
	cols->r = ft_atoi(sl[0]);
	cols->g = ft_atoi(sl[1]);
	cols->b = ft_atoi(sl[2]);
	ft_color_check(cols);
	free_split(sl);
}

void	ass_coords(char *str, t_coord *coords)
{
	char	**sl;

	if (!str)
		ft_parse_error("coordinates, no input string");
	sl = ft_split(str, ',');
	if (!sl || !coords || ft_str_arr_len(sl) != 3)
		ft_parse_error("coordinates, safety checks");
	coords->x = ft_atof(sl[0]);
	coords->y = ft_atof(sl[1]);
	coords->z = ft_atof(sl[2]);
	free_split(sl);
}
