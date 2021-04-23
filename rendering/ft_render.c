/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 21:55:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/23 16:36:26 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// TODO
// Camera rotation
// BMP
// TR. SQ. CY. Intersections

void ass_hitpoint(double t, t_rgb col, int id, t_impact_point *hit)
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

t_ray	ft_primary_ray(t_camera *cam, int x, int y)
{
	t_ray ray;
	t_vec dir = create_pos((double)x, (double)y, cam->cam_dist);
	
	ray.origin = cam->coords;
	ray.direction = normalize(vec_minus(dir, ray.origin));
	return (ray);
}

int		ft_intersect(t_ray ray, t_list **shape_list, t_impact_point *intersection)
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

int		ft_tracer(int x, int y, t_env *env, t_rgb *color)
{
	t_impact_point intersection;
	t_ray	primary_ray;
	t_ray	shadow_ray;
	t_list	*tmp_lst;
	
	// only when cam is on [0;0;Z]
	x = x - env->res.x / 2;
	y = env->res.y / 2 - y;
	intersection.nearest = INFINITY;
	
	primary_ray = ft_primary_ray((t_camera*)(env->cam_list->content), x, y);
	if(ft_intersect(primary_ray, (void*)env->shapes, &intersection))
	{
		tmp_lst = env->light;
		intersection.hitpoint = calc_hitpoint(&primary_ray, (intersection.nearest - 0.001));
		while (tmp_lst != NULL)
		{
			int i = 1;
			shadow_ray = ft_shadow_ray((t_light*)tmp_lst->content, &intersection.hitpoint);
			
			
			// *color = intersection.color;

			
			*color = colors_add(*color, ft_shading(env, &intersection, shadow_ray, (t_light*)tmp_lst->content));
			color_check(color);
			tmp_lst = tmp_lst->next;
			// printf("lightp: %p\n", tmp_lst);
			// printf("lightp: %p\n", tmp_lst);
			// printf("i: %d\n", i);
			i++;
		}
	}
	return (0);
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
			color.r = 0;
			color.g = 0;
			color.b = 0;
			ft_tracer(j, i, env, &color);
			my_pixel_put(img, j, i, create_trgb(0, color.r, color.g, color.b));
			j++;
		}
		i++;
	}
}
