/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/05 16:56:11 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	ass_hitpoint(double t, t_rgb col, int id, t_hit *hit)
{
	if (!hit)
		ft_parse_error("No hitpoint given");
	hit->near = t;
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

t_ray	ft_primary_ray(t_camera *cam, double x, double y)
{
	t_ray		ray;
	t_matrix3x3	matrix;
	t_vec		dir;

	dir = create_pos((double)x, (double)y, cam->cam_dist * 2);
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
			if (i == SPHERE)
				ft_sphere_intersect((t_sphere*)tmp->content, &ray, hitp);
			else if (i == PLANE)
				ft_plane_intersect((t_plane*)tmp->content, &ray, hitp);
			else if (i == TRIANGLE)
				ft_triangle_intersect((t_triangle*)tmp->content, &ray, hitp);
			else if (i == SQUARE)
				ft_square_intersect((t_square*)tmp->content, &ray, hitp);
			else if (i == CYLINDER)
				ft_cylinder_intersect((t_cylinder*)tmp->content, &ray, hitp);
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

	x = x - env->res.x / 2;
	y = env->res.y / 2 - y;
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

t_rgb **ft_render(t_img *img, t_env *env)
{
	int		i;
	int		j;
	int		color;
	t_rgb 	col;
	t_rgb	col_array[env->res.y][env->res.x];

	i = 0;
	while (i < env->res.y)
	{
		j = 0;
		while (j < env->res.x)
		{
			col_array[i][j] = ft_tracer(j, i, env);
			// color = ft_create_trgb(0, col.r, col.g, col.b);
			// if (env->save_to_bmp == 1)
			// {
			// 	// printf("fd: %d\n", env->fd);
			// 	write(env->fd, &color, sizeof(int));
			// }
			// else
			// 	my_pixel_put(img, j, i, ft_create_trgb(0, col.r, col.g, col.b));
			j++;
		}
		i++;
	}
	return (col_array);
}
