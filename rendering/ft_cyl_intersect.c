/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cyl_intersect.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/21 10:25:53 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/21 14:57:29 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int     ft_cylinder_intersect(t_cylinder *cy, t_ray *ray, t_impact_point *hitp)
{   
    // p = ori + dir + t;

    // area_of_parralellogram = (P - cyl_center) x cyl_norm = radius (base * r) whre base = 1;

    // length_of_parra: r^2 = ((P - cyl_center) x cyl_norm)^2
    // subsstitute with line formula:
    //                  r^2 = ((ori + t * dir - cyl_center) x cyl_norm)^2

    // if: ori + t * dir - cyl_center
    //      t * dir + (ori - cyl_center)
    // v = ori - cyl_center;
        // t * dir + v

    // maal de bovenstaande uit:
    // r^2 = ((t * dir + v) x cyl_norm)^2
    // r * r = ((t * dir + v) x cyl_norm).((t * dir + v) x cyl_norm)
    // r * r = ((t * dir) x cyl_norm)^2 + (v x cyl_norm)^2 + 2(t * dir)) x cyl_norm)*(v x cyl_norm)
    
    // a = t^2 . (dir x cyl_norm)^2
    // b = t . 2(dir x cyl_norm).(v x cyl_norm)
    // c = (v x cyl_norm) - r^2

    // dir_x_norm = cross_product(ray->dir, cy->normal)

    t_vec v = vec_minus(ray->origin, cy->coords);
    t_vec dir_x_norm = cross_product(ray->direction, cy->normal);
    t_vec v_x_norm = cross_product(v, cy->normal);

    float a = dot_product(dir_x_norm, dir_x_norm);
    float b = 2 * dot_product(dir_x_norm, v_x_norm);
    float c = dot_product(v_x_norm, v_x_norm) - (cy->r * cy->r);
    float discr = b * b  -  4 * a * c;
    float t1 = 0;
    float t2 = 0;
    if (discr < 0)
        return (0);


	t1 = (-b + sqrt(discr)) / 2;
	t2 = (-b - sqrt(discr)) / 2;
    if (t2 < t1)
        t1 = t2;

    // printf("T: %f\n", t);
    if (t1 < hitp->nearest && t1 >= 0)
	{
		hitp->nearest = t1;
		hitp->color = cy->colors;
		hitp->object_id = cy->id;
        hitp->hitpoint  = calc_hitpoint(ray, t1);
        hitp->normal = normalize(vec_minus(hitp->hitpoint, cy->coords));
	    // hitp->normal = cy->normal;
		return (1);
	}
    
    return (0);
}