/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tracing.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/15 17:49:40 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 17:52:44 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include "math.h"

t_ray	ft_primary_ray(t_camera *cam, double x, double y)
{
	t_ray		ray;
	t_matrix3x3	m;
	t_vec		dir;

	dir = create_pos((double)x, (double)y, cam->cam_dist * 2);
	m.forward = cam->vect_vecs;
	m.right = ft_normalize(ft_cross_product(m.forward, create_pos(0, -1, 0)));
	if (ft_vec_len(m.right) == 0)
		m.right = create_pos(1, 0, 0);
	m.up = ft_cross_product(m.forward, m.right);
	dir = ft_vec_multi_matrix(m, dir);
	ray.origin = cam->coords;
	ray.direction = ft_normalize(vec_minus(dir, ray.origin));
	return (ray);
}

void	ft_shape_if_tree(int i, t_list *shape, t_hit *hitp, t_ray *ray)
{
	if (i == SPHERE)
		ft_sphere_intersect((t_sphere *)shape->content, ray, hitp);
	else if (i == PLANE)
		ft_plane_intersect((t_plane *)shape->content, ray, hitp);
	else if (i == TRIANGLE)
		ft_triangle_intersect((t_triangle *)shape->content, ray, hitp);
	else if (i == SQUARE)
		ft_square_intersect((t_square *)shape->content, ray, hitp);
	else if (i == CYLINDER)
		ft_cylinder_intersect((t_cylinder *)shape->content, ray, hitp);
}

int	ft_intersect(t_ray ray, t_list **shape_list, t_hit *hitp)
{
	int		i;
	t_list	*tmp;

	i = 0;
	if (!shape_list || !hitp)
		return (0);
	while (i <= CYLINDER)
	{
		tmp = shape_list[i];
		while (tmp != NULL)
		{
			ft_shape_if_tree(i, tmp, hitp, &ray);
			tmp = tmp->next;
		}
		i++;
	}
	if (hitp->near < INFINITY)
		return (1);
	return (0);
}

t_rgb	ft_tracer(int x, int y, t_env *env)
{
	t_hit	hitp;
	t_ray	primary_ray;
	t_rgb	color;

	x = x - env->res.x * 0.5;
	y = env->res.y * 0.5 - y;
	hitp.near = INFINITY;
	ft_color_multi(&color, 0);
	primary_ray = ft_primary_ray((t_camera *)(env->cam_list->content), x, y);
	if (ft_intersect(primary_ray, (void *)env->shapes, &hitp))
	{
		hitp.hitpoint = calc_hitpoint(&primary_ray, (hitp.near - 0.001));
		color = ft_shader(env, &hitp);
	}
	return (color);
}
