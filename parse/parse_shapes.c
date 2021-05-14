/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_shapes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:40:31 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/14 15:42:53 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	parse_sphere(char **split, t_list **sphere_lst)
{
	t_sphere	*sph_node;

	sph_node = malloc(sizeof(t_sphere));
	if (!sph_node || !split || !sphere_lst || ft_str_arr_len(split) != 4)
		return (-1);
	else if (ft_strncmp(split[0], ID_SPHERE, 3) != 0)
		ft_parse_error(", invlid sphere id");
	sph_node->id = SPHERE;
	ass_coords(split[1], &sph_node->center);
	sph_node->diam = ft_atof(split[2]) / 2;
	ass_colors(split[3], &sph_node->colors);
	ft_color_check(&sph_node->colors);
	ft_lstadd_back(sphere_lst, ft_lstnew(sph_node));
	return (0);
}

int	parse_plane(char **split, t_list **plane_lst)
{
	t_plane	*plane_node;

	plane_node = malloc(sizeof(t_plane));
	if (!plane_node || !plane_lst | !split || ft_str_arr_len(split) != 4)
		ft_parse_error("plane safety checks");
	else if (ft_strncmp(split[0], ID_PLANE, 3) != 0)
		ft_parse_error(", invlid plane id");
	plane_node->id = PLANE;
	ass_coords(split[1], &plane_node->coords);
	ass_coords(split[2], &plane_node->orient);
	ass_colors(split[3], &plane_node->colors);
	ft_color_check(&plane_node->colors);
	ft_lstadd_back(plane_lst, ft_lstnew(plane_node));
	return (0);
}

int	parse_square(char **split, t_list **square_lst)
{
	t_square	*square_node;

	square_node = malloc(sizeof(t_square));
	if (!square_node || !square_lst | !split || ft_str_arr_len(split) != 5)
		ft_parse_error("square, safety checks");
	else if (ft_strncmp(split[0], ID_SQUARE, 3) != 0)
		ft_parse_error(", invlid square id");
	square_node->id = SQUARE;
	ass_coords(split[1], &square_node->center);
	ass_coords(split[2], &square_node->orient);
	square_node->side_size = ft_atof(split[3]);
	ass_colors(split[4], &square_node->colors);
	ft_color_check(&square_node->colors);
	ft_lstadd_back(square_lst, ft_lstnew(square_node));
	return (0);
}

int	parse_cylinder(char **split, t_list **cylinder_lst)
{
	t_cylinder	*cylinder_node;

	cylinder_node = malloc(sizeof(t_cylinder));
	if (!cylinder_node || !cylinder_lst | !split || ft_str_arr_len(split) != 6)
		ft_parse_error("cylinder, safety checks");
	else if (ft_strncmp(split[0], ID_CYLINDER, 3) != 0)
		ft_parse_error(", invlid cylinder id");
	cylinder_node->id = CYLINDER;
	ass_coords(split[1], &cylinder_node->center);
	ass_coords(split[2], &cylinder_node->ori);
	cylinder_node->r = ft_atof(split[3]) / 2;
	cylinder_node->height = ft_atof(split[4]);
	ass_colors(split[5], &cylinder_node->colors);
	ft_color_check(&cylinder_node->colors);
	ft_lstadd_back(cylinder_lst, ft_lstnew(cylinder_node));
	return (0);
}

int	parse_triangle(char **split, t_list **triangle_lst)
{
	t_triangle	*tri_node;

	tri_node = malloc(sizeof(t_triangle));
	if (!tri_node || !split || !triangle_lst || ft_str_arr_len(split) != 5)
		ft_parse_error("triangle, safety checks");
	else if (ft_strncmp(split[0], ID_TRIANGLE, 3) != 0)
		ft_parse_error(", invlid triangle id");
	tri_node->id = TRIANGLE;
	ass_coords(split[1], &tri_node->frst_pnt);
	ass_coords(split[2], &tri_node->scnd_pnt);
	ass_coords(split[3], &tri_node->thrd_pnt);
	ass_colors(split[4], &tri_node->colors);
	ft_color_check(&tri_node->colors);
	ft_lstadd_front(triangle_lst, ft_lstnew(tri_node));
	return (0);
}
