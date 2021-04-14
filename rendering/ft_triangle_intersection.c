/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_triangle_intersection.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 17:22:28 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/14 19:18:10 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float	ft_triangle_intersect(t_triangle *triangle, t_ray *ray, t_impact_point *intersection)
{
    float t = -1;
    
    t_vec frst_side = vec_minus(triangle->scnd_pnt, triangle->frst_pnt);
    t_vec scd_side = vec_minus(triangle->thrd_pnt, triangle->frst_pnt);
    t_vec normal = cross_product(frst_side, scd_side); // N
    float dot = dot_product(frst_side, normal); // D

    if (dot_product(normal, ray->direction) == 0) // checks if the triangle and the ray are parallel thus intersection occurs at infinity 
        return (0);
    t = (dot - dot_product(normal, ray->origin)) / dot_product(normal, ray->direction);
    
    // printf("dot: %f\n", t);
    if (t >= 0 && t < intersection->nearest)
    {
        intersection->nearest = t;
		intersection->color = triangle->colors;
		intersection->object_id = triangle->id;
		intersection->hitpoint = calc_hitpoint(ray, t);
		intersection->normal = normal;
		return (1);
    }
    
    
    return (0);
}