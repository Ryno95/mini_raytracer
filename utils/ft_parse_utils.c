/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parse_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/05 17:03:23 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/14 17:34:01 by rmeiboom      ########   odam.nl         */
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
	int		split_length;
	int		i;
	int		j;

	sl = ft_split(str, ',');
	split_length = ft_str_arr_len(sl);
	i = 0;
	if (!sl || !cols || split_length != 3)
		ft_parse_error("colors, safety checks");
	while (i < split_length)
	{
		j = 0;
		while (sl[i][j])
		{
			if (!ft_isdigit(sl[i][j]) && sl[i][j] != '.' && sl[i][j] != '-')
				ft_parse_error("number contains non numerical values");
			j++;
		}
		i++;
	}
	cols->r = ft_atoi(sl[0]);
	cols->g = ft_atoi(sl[1]);
	cols->b = ft_atoi(sl[2]);
	free_split(sl);
}

void	ass_coords(char *str, t_vec *coords)
{
	char	**sl;
	int		split_length;
	int		i;
	int		j;

	sl = ft_split(str, ',');
	split_length = ft_str_arr_len(sl);
	i = 0;
	if (!sl || !coords || ft_str_arr_len(sl) != 3 || !str)
		ft_parse_error("coordinates, safety checks");
	while (i < split_length)
	{
		j = 0;
		while (sl[i][j])
		{
			if (!ft_isdigit(sl[i][j]) && sl[i][j] != '.' && sl[i][j] != '-')
				ft_parse_error("number contains non numerical values");
			j++;
		}
		i++;
	}
	coords->x = ft_atof(sl[0]);
	coords->y = ft_atof(sl[1]);
	coords->z = ft_atof(sl[2]);
	free_split(sl);
}
