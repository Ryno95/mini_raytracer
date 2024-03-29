/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:31:58 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/21 12:21:30 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include "../mlx/mlx.h"
#include <math.h>

int	parse_res(char **spl_str, t_res *res)
{
	if (!spl_str || !res || ft_str_arr_len(spl_str) != 3)
		ft_parse_error("resolution, safety checks");
	else if (res->id == 'R' || ft_strncmp(spl_str[0], ID_RES, 2) != 0)
		ft_parse_error(", multiple/wrong id resolution");
	res->id = spl_str[0][0];
	res->x = ft_atoi(spl_str[1]);
	res->y = ft_atoi(spl_str[2]);
	if (res->x <= 0 || res->y <= 0)
		ft_parse_error("resolution, invalid width and height");
	return (0);
}

int	parse_amb_light(char **spl_str, t_amb_light *am_lt)
{
	if (!spl_str || !am_lt || ft_str_arr_len(spl_str) != 3)
		ft_parse_error("ambient light, safety checks");
	else if (am_lt->id == 'A' || ft_strncmp(spl_str[0], ID_AMB_LIGHT, 2) != 0)
		ft_parse_error(", multiple/wrong id amb lighting");
	am_lt->id = spl_str[0][0];
	am_lt->ratio = ft_atof(spl_str[1]);
	if (am_lt->ratio > 1 || am_lt->ratio < 0)
		ft_parse_error("ambient light, invalid brightness ratio");
	ass_colors(spl_str[2], &am_lt->colors);
	ft_color_multi(&am_lt->colors, am_lt->ratio);
	ft_color_check(&am_lt->colors);
	return (0);
}

int	parse_cam(char **spl_str, t_list **cam)
{
	t_camera	*cam_node;

	cam_node = malloc(sizeof(t_camera));
	if (!cam_node || ft_str_arr_len(spl_str) != 4)
		ft_parse_error("camera, malloc or array length");
	else if (ft_strncmp(spl_str[0], ID_CAMERA, 2) != 0)
		ft_parse_error("wrong camera id");
	cam_node->id = 'c';
	ass_coords(spl_str[1], &cam_node->coords);
	ass_coords(spl_str[2], &cam_node->ori);
	cam_node->ori = ft_normalize(cam_node->ori);
	cam_node->fov = ft_atoi(spl_str[3]);
	if (cam_node->fov < 0 || cam_node->fov > 180)
		ft_parse_error("camera fov should be in range 0-180");
	ft_lstadd_front(cam, ft_lstnew(cam_node));
	return (0);
}

int	parse_light(char **split, t_list **light_lst)
{
	t_light	*light_node;

	light_node = malloc(sizeof(t_light));
	if (!split || !light_lst || !light_node || ft_str_arr_len(split) != 4)
		ft_parse_error("light source, safety checks");
	else if (ft_strncmp(split[0], ID_LIGHT, 2) != 0)
		ft_parse_error("wrong light id");
	light_node->id = 'l';
	ass_coords(split[1], &light_node->coords);
	light_node->brightness = ft_atof(split[2]);
	if (light_node->brightness < 0 || light_node->brightness > 1)
		ft_parse_error("light source, invalid brightness ratio");
	ass_colors(split[3], &light_node->colors);
	ft_color_check(&light_node->colors);
	ft_lstadd_front(light_lst, ft_lstnew(light_node));
	return (0);
}
