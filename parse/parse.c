/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:27:17 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/04 21:55:15 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"


static int	parse_res(char *line, t_res *res)
{
	// R 1920 1080

	char **split_line;
	split_line = ft_split(line, ' ');
	if (!split_line)
		return (-1);
	else
	{
		res->id = split_line[0][0];
		res->x = ft_atoi(split_line[1]);
		res->y = ft_atoi(split_line[2]);
	}
	printf("ID: %c\nX: %d\nY: %d\n", res->id, res->x, res->y);
	free_split(split_line);
	return (0);
}

static int	parse_amb_light(char *line, t_amb_light *am_lt)
{
	char **sl;
	sl = ft_split(line, ' ');
	if (!sl)
		return (-1);
	else
	{
		am_lt->id = sl[0][0];
		// TODO: Right ft_atof();
		am_lt->ratio = ft_atof(line);
		while (ft_isdigit(*line))
			line++;
		// TODO: Assignation of RGB struct
	}
	free_split(sl);
	return (0);
}

int			parse(char *line, t_env *env)
{
	if (line[0] == '\n')
		return (0);
	if (*line == 'R')
		parse_res(line, &env->res);
	else if (*line == 'A')
		parse_amb_light(line, &env->amb_light);


	printf("ID: %c\nX: %d\nY: %d\n", env->res.id, env->res.x, env->res.y);
	// if tree by identifier
		// if identifier
			// pass indentified struct to corresponding function
			// if (*line == 'R')
				// return (parse_camera(line, env.camera));

	return (0);
}


// ft_atof() alpha to float
// ft_str_split_set() for all white spaces