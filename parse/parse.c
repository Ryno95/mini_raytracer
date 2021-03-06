/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:27:17 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/06 21:55:21 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// check that values are positive where needed
int	parse_res(char **spl_str, t_res *res)
{
	// R 1920 1080

	if (!spl_str || !res)
		return (-1);
	res->id = spl_str[0][0];
	res->x = ft_atoi(spl_str[1]);
	res->y = ft_atoi(spl_str[2]);
	return (0);
}

int	parse_amb_light(char **spl_str, t_amb_light *am_lt)
{
	char **sl;
	if (!spl_str || !am_lt)
		return (-1);
	am_lt->id = spl_str[0][0];
	am_lt->ratio = ft_atof(spl_str[1]);
	ass_colors(spl_str[2], &am_lt->colors);
	
	return (0);
}

int	parse_cam(char **spl_str, t_list **cam)
{
	// c   -50.0,0,20   0,0,1   70
	int vec_len;
	t_camera *cam_node;
	
	cam_node = malloc(sizeof(t_camera));
	cam_node->id = CAMERA;
	ass_coords(spl_str[1], &cam_node->coords);
	
	// What is best prectice for this? If 3d vect isn't correct??? Error? Or Assign the correct version???
	vec_len = ft_vec_len(cam_node->coords);
	cam_node->vect_coords.x = cam_node->coords.x / vec_len;
	cam_node->vect_coords.y = cam_node->coords.y / vec_len;
	cam_node->vect_coords.z = cam_node->coords.z / vec_len;
	cam_node->fov = ft_atoi(spl_str[3]);
	
	if (cam_node->fov < 0)
		cam_node->fov = 0;
	else if (cam_node->fov > 180)
		cam_node->fov = 180;
		
	ft_lstadd_front(cam, ft_lstnew(cam_node));
	return (0);
}

int	parse(t_env *env)
{
	if (*env->spl_str[0] == '\n')
		return (0);
	if (**env->spl_str == 'R')
		return(parse_res(env->spl_str, &env->res));
	else if (**env->spl_str == 'A')
		return(parse_amb_light(env->spl_str, &env->amb_light));
	else if (**env->spl_str == 'c')
		return(parse_cam(env->spl_str, &env->camera));
	// else if (**env->spl_str == 'l')
	
	// if tree by identifier
		// if identifier
			// pass indentified struct to corresponding function
			// if (*line == 'R')
				// return (parse_camera(line, env.camera));

	return (0);
}


// ft_atof() alpha to float
// ft_str_split_set() for all white spaces