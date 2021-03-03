/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:27:17 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/03 13:43:07 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"


int		parse(char *line, t_env *env)
{
	if (line[0] == '\n')
		return (0);
	// if tree by identifier
		// if identifier
			// pass indentified struct to corresponding function
			// if (*line == 'R')
				// return (parse_camera(line, env.camera));

	return (0);
}


// ft_atof() alpha to float
// ft_str_split_set() for all white spaces