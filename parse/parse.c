/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:27:17 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/06 22:41:30 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// check that values are positive where needed
int	parse_res(t_env *env)
{
	// R 1920 1080

	if (!env->spl_str)
		return (-1);
	env->res.id = env->spl_str[0][0];
	env->res.x = ft_atoi(env->spl_str[1]);
	env->res.y = ft_atoi(env->spl_str[2]);
	return (0);
}

int	parse_amb_light(t_env *env)
{
	char **sl;
	if (!env->spl_str)
		return (-1);
	env->amb_light.id = env->spl_str[0][0];
	env->amb_light.ratio = ft_atof(env->spl_str[1]);
	ass_colors(env->spl_str[2], &env->amb_light.colors);
	
	return (0);
}

int	parse_cam(t_env *env)
{
	// c   -50.0,0,20   0,0,1   70
	int vec_len;
	t_camera *cam_node;
	
	cam_node = malloc(sizeof(t_camera));
	if(!cam_node || !env)
	cam_node->id = CAMERA;
	ass_coords(env->spl_str[1], &cam_node->coords);
	
	// What is best prectice for this? If 3d vect isn't correct??? Error? Or Assign the correct version???
	vec_len = ft_vec_len(cam_node->coords);
	cam_node->vect_coords.x = cam_node->coords.x / vec_len;
	cam_node->vect_coords.y = cam_node->coords.y / vec_len;
	cam_node->vect_coords.z = cam_node->coords.z / vec_len;
	cam_node->fov = ft_atoi(env->spl_str[3]);
	
	if (cam_node->fov < 0)
		cam_node->fov = 0;
	else if (cam_node->fov > 180)
		cam_node->fov = 180;
		
	ft_lstadd_front(&env->cam_list, ft_lstnew(cam_node));
	return (0);
}

int parse_light(t_env *env)
{
	t_light *light_node;
	light_node = malloc(sizeof(t_light));
	if (!env || !light_node)
		return (-1);

	light_node->id = LIGHT;
	ass_coords(env->spl_str[1], &light_node->coords);
	light_node->brightness = ft_atof(env->spl_str[2]);
	ass_colors(env->spl_str[3], &light_node->colors);
	
	ft_lstadd_front(&env->light, ft_lstnew(light_node));
	
	return (0);
}

int	parse(t_env *env)
{
	if (*env->spl_str[0] == '\n')
		return (0);
	if (**env->spl_str == 'R')
		return(parse_res(env));
	else if (**env->spl_str == 'A')
		return(parse_amb_light(env));
	else if (**env->spl_str == 'c')
		return(parse_cam(env));
	else if (**env->spl_str == 'l')
		return(parse_light(env));
	
	// if tree by identifier
		// if identifier
			// pass indentified struct to corresponding function
			// if (*line == 'R')
				// return (parse_camera(line, env.camera));

	return (0);
}


// ft_atof() alpha to float
// ft_str_split_set() for all white spaces