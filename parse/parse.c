/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:27:17 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/21 13:41:26 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include "../gnl/get_next_line.h"
#include <fcntl.h>
#include <math.h>

static void	ft_calc_cam_dist(t_env *env)
{
	t_list		*tmp;
	t_camera	*cam;

	tmp = env->cam_list;
	while (tmp)
	{
		cam = ((t_camera *)(tmp->content));
		cam->cam_dist = 0.5 * (env->res.x / 2)
			/ tan((cam->fov * (M_PI / 180)) / 2);
		tmp = tmp->next;
	}
}

int	parse_tree(t_env *env)
{
	if (**env->spl_str == 'R')
		return (parse_res(env->spl_str, &env->res));
	else if (**env->spl_str == 'A')
		return (parse_amb_light(env->spl_str, &env->amb_light));
	else if (**env->spl_str == 'c' && env->spl_str[0][1] != 'y')
		return (parse_cam(env->spl_str, &env->cam_list));
	else if (**env->spl_str == 'l')
		return (parse_light(env->spl_str, &env->light));
	else if (ft_strncmp("sp", env->spl_str[0], ft_strlen(env->spl_str[0])) == 0)
		return (parse_sphere(env->spl_str, &env->shapes[SPHERE]));
	else if (ft_strncmp("pl", env->spl_str[0], ft_strlen(env->spl_str[0])) == 0)
		return (parse_plane(env->spl_str, &env->shapes[PLANE]));
	else if (ft_strncmp("sq", env->spl_str[0], ft_strlen(env->spl_str[0])) == 0)
		return (parse_square(env->spl_str, &env->shapes[SQUARE]));
	else if (ft_strncmp("cy", env->spl_str[0], ft_strlen(env->spl_str[0])) == 0)
		return (parse_cylinder(env->spl_str, &env->shapes[CYLINDER]));
	else if (ft_strncmp("tr", env->spl_str[0], ft_strlen(env->spl_str[0])) == 0)
		return (parse_triangle(env->spl_str, &env->shapes[TRIANGLE]));
	return (0);
}

int	parse(char *file_name, t_env *env)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_parse_error("Open failed");
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (*line != '\0')
		{
			env->spl_str = ft_split(line, ' ');
			if (!env->spl_str || ret < 0)
				ft_exit(env, "Error\nCan't split invalid line");
			parse_tree(env);
			free_split(env->spl_str);
		}
		free(line);
	}
	if (!env->res.id)
		ft_exit(env, "Error\nNo resolution given!");
	ft_calc_cam_dist(env);
	return (0);
}
