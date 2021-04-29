/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/29 20:36:58 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// TODO
// Camera rotation
// BMP
// TR. SQ. CY. Intersections

void ass_hitpoint(double t, t_rgb col, int id, t_hit *hit)
{
	if (!hit)
		ft_parse_error("No hitpoint given");
	hit->nearest = t;
	hit->color = col;
	hit->object_id = id;
}

t_vec vec_by_vec(t_vec a, t_vec b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

t_ray	ft_primary_ray(t_camera *cam, double x, double y, double z)
{
	t_ray ray;

	t_matrix3x3 matrix;

 	// z /= tan(cam->fov * 0.5);
	 z = cam->cam_dist;
	t_vec dir = create_pos((double)x, (double)y, z * 2);
	matrix.forward = cam->vect_coords;
	matrix.right = normalize(cross_product(matrix.forward, create_pos(0, -1, 0)));
	if (vec_len(matrix.right) == 0)
		matrix.right = create_pos(1,0,0);
	matrix.up = cross_product(matrix.forward, matrix.right);
	dir = ft_vec_multi_matrix(matrix, dir);
	
	ray.origin = cam->coords;
	ray.direction = normalize(vec_minus(dir, ray.origin));
	return (ray);
}

int		ft_intersect(t_ray ray, t_list **shape_list, t_hit *intersection)
{
	int i;
	t_list *tmp_lst;

	i = 0;
	if (!shape_list || !intersection)
		return (0);
	while (i <= CYLINDER)
	{
		tmp_lst = shape_list[i];
		while (tmp_lst != NULL)
		{
			if (i == SPHERE)
				ft_sphere_intersect((t_sphere*)tmp_lst->content, &ray, intersection);
			else if (i == PLANE)
				ft_plane_intersect((t_plane*)tmp_lst->content, &ray, intersection);
			else if (i == TRIANGLE)
				ft_triangle_intersect((t_triangle*)tmp_lst->content, &ray, intersection);
			else if (i == SQUARE)
				ft_square_intersect((t_square*)tmp_lst->content, &ray, intersection);
			else if (i == CYLINDER)
				ft_cylinder_intersect((t_cylinder*)tmp_lst->content, &ray, intersection);
			tmp_lst = tmp_lst->next;
		}
		i++;
	}
	if (intersection->nearest < INFINITY)
		return (1);
	return (0);
}

t_rgb		ft_tracer(int x, int y, t_env *env)
{
	t_hit intersection;
	t_ray	primary_ray;
	t_ray	shadow_ray;
	t_list	*tmp_lst;
	t_rgb	color;
	
	x = x - env->res.x / 2;
	y = env->res.y / 2 - y;
	// double z = env->res.y / 2;
	double z = 0;
	intersection.nearest = INFINITY;
	
	color_multi(&color, 0);
	primary_ray = ft_primary_ray((t_camera*)(env->cam_list->content), x, y, z);
	if(ft_intersect(primary_ray, (void*)env->shapes, &intersection))
	{
		intersection.hitpoint = calc_hitpoint(&primary_ray, (intersection.nearest - 0.001));
		color = ft_shader(env, &intersection);
	}
	return (color);
}

void ft_render(t_img *img, t_env *env)
{
	int		i;
	int		j;
	t_rgb color;

	i = 0;
	while (i < env->res.y)
	{
		j = 0;
		while (j < env->res.x)
		{
			color = ft_tracer(j, i, env);
			my_pixel_put(img, j, i, create_trgb(0, color.r, color.g, color.b));
			j++;
		}
		i++;
	}
}
