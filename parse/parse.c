/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:27:17 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/05 22:19:41 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// check that values are positive where needed
int	parse_res(char *line, t_res *res)
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
	free_split(split_line);
	return (0);
}

int	parse_amb_light(char *line, t_amb_light *am_lt)
{
	char **sl;
	sl = ft_split(line, ' ');
	if (!sl)
		return (-1);
	am_lt->id = sl[0][0];
	am_lt->ratio = ft_atof(sl[1]);
	while (ft_isdigit(*line))
		line++;
	ass_colors(sl[2], &am_lt->colors);
	free_split(sl);
	
	return (0);
}


// t_camera cam_list(void *content)
// {
// 	 t_list *node;

	 
// }

int	parse_cam(char *line, t_camera *cam)
{
	// c   -50.0,0,20   0,0,1   70
	// When passing a pointer, it's initial val is NULL fuckface!!!!
	// Make a new t_camera *
	// Fill the values
	// Add it to the cam_list
	char **sl;
	int vec_len;
	// t_list	*camlist;
	sl = ft_split(line, ' ');
	if (!sl)
		return (-1);
	// if (!camlist)
	// 	camlist = ft_lstnew(cam);
	// if (!camlist)
		// return (-1);
	// cam->id = CAM;
	cam->id = 99;
	printf("ID: %d\n", cam->id);
	// cam->id = CAM;
	// ass_coords(sl[1], &cam->coords);
	// vec_len = ft_vec_len(cam->coords);
	// cam->vect_coords.x = cam->coords.x / vec_len;
	// cam->vect_coords.y = cam->coords.y / vec_len;
	// cam->vect_coords.z = cam->coords.z / vec_len;
	// cam->fov = ft_atoi(sl[3]);
	// if (cam->fov < 0)
	// 	cam->fov = 0;
	// else if (cam->fov > 180)
	// 	cam->fov = 180;
	
	return (0);
}

int	parse(char *line, t_env *env)
{
	if (line[0] == '\n')
		return (0);
	if (*line == 'R')
		return(parse_res(line, &env->res));
	else if (*line == 'A')
		return(parse_amb_light(line, &env->amb_light));
	else if (*line == 'c')
		return(parse_cam(line, env->camera));


	// if tree by identifier
		// if identifier
			// pass indentified struct to corresponding function
			// if (*line == 'R')
				// return (parse_camera(line, env.camera));

	return (0);
}


// ft_atof() alpha to float
// ft_str_split_set() for all white spaces