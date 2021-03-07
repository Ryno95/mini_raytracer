/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:27:17 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/07 21:09:22 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// TODO ERROR MANAGEMENT:
	// VECT_COORDS
	// SPLIT LENGTH
	// ROUND FLOAT 2
int	parse(t_env *env)
{
	printf("%s\n", env->spl_str[0]);
	if (**env->spl_str == 'R')
		return(parse_res(env->spl_str, &env->res));
	else if (**env->spl_str == 'A')
		return(parse_amb_light(env->spl_str, &env->amb_light));
	else if (**env->spl_str == 'c' && env->spl_str[0][1] != 'y')
		return(parse_cam(env->spl_str, &env->cam_list));
	else if (**env->spl_str == 'l')
		return(parse_light(env->spl_str, &env->light));
	else if (ft_strncmp("sp", env->spl_str[0], ft_strlen(env->spl_str[0])) == 0)
		return(parse_sphere(env->spl_str, &env->sphere_lst));
	else if (ft_strncmp("pl", env->spl_str[0], ft_strlen(env->spl_str[0])) == 0)
		return(parse_plane(env->spl_str, &env->plane_lst));
	else if (ft_strncmp("sq", env->spl_str[0], ft_strlen(env->spl_str[0])) == 0)
		return(parse_square(env->spl_str, &env->square_lst));
	else if (ft_strncmp("cy", env->spl_str[0], ft_strlen(env->spl_str[0])) == 0)
		return(parse_cylinder(env->spl_str, &env->cylinder_lst));
	else if (ft_strncmp("tr", env->spl_str[0], ft_strlen(env->spl_str[0])) == 0)
		return(parse_triangle(env->spl_str, &env->triangle_lst));

	return (0);
}
