/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_triangle_intersection.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 17:22:28 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/23 16:36:26 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int     ft_is_inside_triangle(t_triangle *tri, t_vec inters_p, t_vec normal)
{
    t_vec side;
    t_vec cross;
    
    side = vec_minus(tri->scnd_pnt, tri->frst_pnt);
    cross = cross_product(side, vec_minus(inters_p, tri->frst_pnt));
    if (dot_product(normal, cross) < 0)
        return (0);
        
    side = vec_minus(tri->frst_pnt, tri->thrd_pnt);
    cross = cross_product(side, vec_minus(inters_p, tri->thrd_pnt));
    if (dot_product(normal, cross) < 0)
        return (0);
        
    side = vec_minus(tri->thrd_pnt, tri->scnd_pnt);
    cross = cross_product(side, vec_minus(inters_p, tri->scnd_pnt));
    if (dot_product(normal, cross) < 0)
        return (0);
        
    return (1);
}

double	ft_triangle_intersect(t_triangle *triangle, t_ray *ray, t_impact_point *intersection)
{
    double t = -1;
    
    t_vec frst_side;
    t_vec scd_side;;
    t_vec normal; // N
    double angle;
    t_vec point;

    frst_side = vec_minus(triangle->scnd_pnt, triangle->frst_pnt);
    scd_side = vec_minus(triangle->thrd_pnt, triangle->frst_pnt);
    normal = normalize(cross_product(frst_side, scd_side));
    angle = dot_product(normal, ray->direction);;
    if (fabs(angle) < 0.00001) // checks if the triangle and the ray are parallel thus intersection occurs at infinity 
        return (0);
    t = dot_product(normal, vec_minus(triangle->frst_pnt, ray->origin)) / angle;
    point = calc_hitpoint(ray, t);
    if (t >= 0 && t < intersection->nearest && ft_is_inside_triangle(triangle, point, normal))
    {
        // ass_hitpoint(t, triangle->colors, triangle->id, intersection);
        intersection->nearest = t;
		intersection->color = triangle->colors;
		intersection->object_id = triangle->id;
	    intersection->hitpoint = point;
		intersection->normal = normal;
        if (dot_product(normal, ray->direction) > 0)
            intersection->normal = vec_multiply(normal, -1);
            
		return (1);
    }
    
        
    return (0);
}