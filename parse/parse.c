/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:27:17 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/07 13:33:47 by rmeiboom      ########   odam.nl         */
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

int parse_light(char **split, t_list **light_lst)
{
	t_light *light_node;
	light_node = malloc(sizeof(t_light));
	if (!split || !light_lst || !light_node)
		return (-1);

	light_node->id = LIGHT;
	ass_coords(split[1], &light_node->coords);
	light_node->brightness = ft_atof(split[2]);
	ass_colors(split[3], &light_node->colors);
	
	ft_lstadd_front(light_lst, ft_lstnew(light_node));
	
	return (0);
}

int	parse_sphere(char **split, t_list **sphere_lst)
{
	t_sphere *sph_node;

	sph_node = malloc(sizeof(t_sphere));
	if (!sph_node || !split || !sphere_lst)
		return (-1);

	sph_node->id = SPHERE;
	ass_coords(split[1], &sph_node->coords);
	sph_node->diam = ft_atof(split[2]);
	ass_colors(split[3], &sph_node->colors);

	ft_lstadd_back(sphere_lst, ft_lstnew(sph_node));
	return (0);
}

int parse_plane(char **split, t_list **plane_lst)
{
	t_plane *plane_node;
	
	plane_node = malloc(sizeof(t_plane));
	if (!plane_node || !plane_lst | !split)
		ft_parse_error("plane");
	
	plane_node->id = PLANE;
	ass_coords(split[1], &plane_node->coords);
	ass_coords(split[2], &plane_node->vect_coords);
	ass_colors(split[3], &plane_node->colors);

	ft_lstadd_back(plane_lst, ft_lstnew(plane_node));
	
	return (0);
}

int parse_square(char **split, t_list **square_lst)
{
	t_square *square_node;
	
	square_node = malloc(sizeof(t_square));
	if (!square_node || !square_lst | !split)
		ft_parse_error("square");
	
	square_node->id = SQUARE;
	ass_coords(split[1], &square_node->coords);
	ass_coords(split[2], &square_node->vect_coords);
	square_node->side_size = ft_atof(split[3]);
	ass_colors(split[4], &square_node->colors);

	ft_lstadd_back(square_lst, ft_lstnew(square_node));
	
	return (0);
}

int parse_cylinder(char **split, t_list **cylinder_lst)
{
	t_cylinder *cylinder_node;
	
	cylinder_node = malloc(sizeof(t_cylinder));
	if (!cylinder_node || !cylinder_lst | !split)
		ft_parse_error("cylinder");
	
	cylinder_node->id = CYLINDER;
	ass_coords(split[1], &cylinder_node->coords);
	ass_coords(split[2], &cylinder_node->vect_coords);
	cylinder_node->diamtr = ft_atof(split[3]);
	cylinder_node->height = ft_atof(split[4]);
	ass_colors(split[5], &cylinder_node->colors);

	ft_lstadd_back(cylinder_lst, ft_lstnew(cylinder_node));
	
	return (0);
}

int parse_triangle(char **split, t_list **triangle_lst)
{
	t_triangle *tri_node;

	tri_node = malloc(sizeof(t_triangle));
	if (!tri_node || !split || !triangle_lst)
		ft_parse_error("triangle, safety checks");

	tri_node->id = TRIANGLE;
	// See if you can dinamically assign the points
	// while (i <= 3)
	ass_coords(split[1], &tri_node->frst_pnt);
	ass_coords(split[2], &tri_node->scnd_pnt);
	ass_coords(split[3], &tri_node->thrd_pnt);
	ass_colors(split[4], &tri_node->colors);
	
	ft_lstadd_front(triangle_lst, ft_lstnew(tri_node));

	return (0);
}

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
