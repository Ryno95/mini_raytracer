/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:31:58 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/29 20:29:37 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// check that values are positive where needed
int	parse_res(char **spl_str, t_res *res)
{
	// R 1920 1080
	if (!spl_str || !res || ft_str_arr_len(spl_str) != 3)
		ft_parse_error("resolution, safety checks");
	res->id = spl_str[0][0];
	// find a way to check screen max and min
	res->x = ft_atoi(spl_str[1]);
	res->y = ft_atoi(spl_str[2]);
	return (0);
}

int	parse_amb_light(char **spl_str, t_amb_light *am_lt)
{
	char **sl;
	if (!spl_str || !am_lt || ft_str_arr_len(spl_str) != 3)
		ft_parse_error("ambient light, safety checks");
	am_lt->id = spl_str[0][0];
	am_lt->ratio = ft_atof(spl_str[1]);
	ass_colors(spl_str[2], &am_lt->colors);

	if (am_lt->ratio > 1 || am_lt->ratio < 0)
		ft_parse_error("ambient light, ratio out of bounds");

	return (0);
}

int	parse_cam(char **spl_str, t_list **cam, t_res *res)
{
	// c   -50.0,0,20   0,0,1   70
	int vl;
	t_camera *cam_node;

	cam_node = malloc(sizeof(t_camera));
	if (!cam_node || ft_str_arr_len(spl_str) != 4)
		ft_parse_error("camera, malloc or array length");
	cam_node->id = 'c';
	ass_coords(spl_str[1], &cam_node->coords);

	// What is best prectice for this? If 3d vect isn't correct??? Error? Or Assign the correct version???
	vl = vec_len(cam_node->coords);
	cam_node->vect_coords.x = cam_node->coords.x / vl;
	cam_node->vect_coords.y = cam_node->coords.y / vl;
	cam_node->vect_coords.z = cam_node->coords.z / vl;
	cam_node->fov = ft_atoi(spl_str[3]);
	cam_node->cam_dist = (res->x / 2) / tan(cam_node->fov / 2);
	if (cam_node->fov < 0)
		cam_node->fov = 0;
	else if (cam_node->fov > 180)
		cam_node->fov = 180;

	ft_lstadd_front(cam, ft_lstnew(cam_node));
	return (0);
}

int parse_light(char **split, t_list **light_lst)
{
	t_light *light_node;
	light_node = malloc(sizeof(t_light));
	if (!split || !light_lst || !light_node || ft_str_arr_len(split) != 4)
		ft_parse_error("light source, safety checks");

	light_node->id = 'l';
	ass_coords(split[1], &light_node->coords);
	
	light_node->brightness = ft_atof(split[2]);
	if (light_node->brightness < 0 || light_node->brightness > 1)
		ft_parse_error("light source, brightness ratio");

	ass_colors(split[3], &light_node->colors);

	ft_lstadd_front(light_lst, ft_lstnew(light_node));

	return (0);
}
