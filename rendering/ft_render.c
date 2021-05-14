/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/14 17:14:37 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include "math.h"

int	ass_hitpoint(double t, t_rgb col, int id, t_hit *hit)
{
	if (!hit)
		return (0);
	hit->near = t;
	hit->color = col;
	hit->object_id = id;
	return (1);
}

t_ray	ft_primary_ray(t_camera *cam, double x, double y)
{
	t_ray		ray;
	t_matrix3x3	matrix;
	t_vec		dir;

	dir = create_pos((double)x, (double)y, cam->cam_dist * 2);
	matrix.forward = cam->vect_vecs;
	matrix.right = normalize(cross_product(matrix.forward, create_pos(0, -1, 0)));
	if (vec_len(matrix.right) == 0)
		matrix.right = create_pos(1,0,0);
	matrix.up = cross_product(matrix.forward, matrix.right);
	dir = ft_vec_multi_matrix(matrix, dir);
	ray.origin = cam->coords;
	ray.direction = normalize(vec_minus(dir, ray.origin));
	return (ray);
}

void	ft_shape_if_tree(int i, t_list *shape, t_hit *hitp, t_ray *ray)
{
	if (i == SPHERE)
		ft_sphere_intersect((t_sphere*)shape->content, ray, hitp);
	else if (i == PLANE)
		ft_plane_intersect((t_plane*)shape->content, ray, hitp);
	else if (i == TRIANGLE)
		ft_triangle_intersect((t_triangle*)shape->content, ray, hitp);
	else if (i == SQUARE)
		ft_square_intersect((t_square*)shape->content, ray, hitp);
	else if (i == CYLINDER)
		ft_cylinder_intersect((t_cylinder*)shape->content, ray, hitp);
}

int		ft_intersect(t_ray ray, t_list **shape_list, t_hit *hitp)
{
	int i;
	t_list *tmp;

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

t_rgb		ft_tracer(int x, int y, t_env *env)
{
	t_hit intersection;
	t_ray	primary_ray;
	t_rgb	color;

	x = x - env->res.x * 0.5;
	y = env->res.y * 0.5 - y;
	intersection.near = INFINITY;

	ft_color_multi(&color, 0);
	primary_ray = ft_primary_ray((t_camera*)(env->cam_list->content), x, y);
	if(ft_intersect(primary_ray, (void*)env->shapes, &intersection))
	{
		intersection.hitpoint = calc_hitpoint(&primary_ray, (intersection.near - 0.001));
		color = ft_shader(env, &intersection);
	}
	return (color);
}

int ft_render(t_env *env)
{
	int		i;
	int		j;
	int		k;
	t_rgb	color;

	env->col_array = (t_3rgb *)malloc(env->res.y * env->res.x * sizeof(t_3rgb));
	if (!env->col_array)
		return (0);
				// ft_error("You fucked up!", env);
	i = 0;
	k = 0;
	while (i < env->res.y)
	{
		j = 0;
		while (j < env->res.x)
		{
			color = ft_tracer(j, i, env);
			if (env->save_to_bmp == 1)
				k = (env->res.y - i - 1) * env->res.x + j;
			else
				k = i * env->res.x + j;
			env->col_array[k].r = (uint8_t)color.r;
			env->col_array[k].g = (uint8_t)color.g;
			env->col_array[k].b = (uint8_t)color.b;
			j++;
		}
		i++;
	}
	return (1);
}
