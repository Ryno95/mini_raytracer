/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:31:58 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/13 12:51:48 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <math.h>

// Check max screen res!
int	parse_res(char **spl_str, t_res *res)
{
	if (!spl_str || !res || ft_str_arr_len(spl_str) != 3)
		ft_parse_error("resolution, safety checks");
	if (res->id == 'R')
		ft_parse_error(", multiple resolutions not allowed");
	res->id = spl_str[0][0];
	res->x = ft_atoi(spl_str[1]);
	res->y = ft_atoi(spl_str[2]);
	if (res->x < 0 || res->y < 0 || res->x > MAX_WIDTH || res->y > MAX_HEIGHT)
		ft_parse_error("resolution, invalid width and height");
	return (0);
}

int	parse_amb_light(char **spl_str, t_amb_light *am_lt)
{
	if (!spl_str || !am_lt || ft_str_arr_len(spl_str) != 3)
		ft_parse_error("ambient light, safety checks");
	if (am_lt->id == 'A')
		ft_parse_error(", multiple ambient lights not allowed");
	am_lt->id = spl_str[0][0];
	am_lt->ratio = ft_atof(spl_str[1]);
	if (am_lt->ratio > 1 || am_lt->ratio < 0)
		ft_parse_error("ambient light, invalid brightness ratio");
	ass_colors(spl_str[2], &am_lt->colors);
	ft_color_multi(&am_lt->colors, am_lt->ratio);
	ft_color_check(&am_lt->colors);
	return (0);
}

int	parse_cam(char **spl_str, t_list **cam, t_res *res)
{
	t_camera	*cam_node;

	cam_node = malloc(sizeof(t_camera));
	if (!cam_node || ft_str_arr_len(spl_str) != 4)
		ft_parse_error("camera, malloc or array length");
	cam_node->id = 'c';
	ass_coords(spl_str[1], &cam_node->coords);
	ass_coords(spl_str[2], &cam_node->vect_coords);
	cam_node ->vect_coords = normalize(cam_node->vect_coords);
	cam_node->fov = ft_atoi(spl_str[3]);
	if (cam_node->fov < 0)
		cam_node->fov = 0;
	else if (cam_node->fov > 180)
		cam_node->fov = 180;
	cam_node->cam_dist = 0.5 * (res->x / 2)
		/ tan((cam_node->fov * (M_PI / 180)) / 2);
	ft_lstadd_front(cam, ft_lstnew(cam_node));
	return (0);
}

int	parse_light(char **split, t_list **light_lst)
{
	t_light	*light_node;

	light_node = malloc(sizeof(t_light));
	if (!split || !light_lst || !light_node || ft_str_arr_len(split) != 4)
		ft_parse_error("light source, safety checks");
	light_node->id = 'l';
	ass_coords(split[1], &light_node->coords);
	light_node->brightness = ft_atof(split[2]);
	if (light_node->brightness < 0 || light_node->brightness > 1)
		ft_parse_error("light source, invalid brightness ratio");
	ass_colors(split[3], &light_node->colors);
	ft_lstadd_front(light_lst, ft_lstnew(light_node));
	return (0);
}
