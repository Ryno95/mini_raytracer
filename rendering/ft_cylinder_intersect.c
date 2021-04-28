/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cylinder_intersect.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/21 10:25:53 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/28 18:41:04 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"




t_vec   ft_cyl_normal(double r, t_coord hitp, t_coord center, t_vec ori)
{
    double a;
    double c;
    t_vec normal;
    t_vec center_hitp = vec_minus(hitp, center);
    a = dot_product(center_hitp, ori); // use for height check
    t_vec translate = vec_add(center, vec_multiply(ori, a));
    normal = normalize(vec_minus(hitp, translate));
    // c = pow(vec_len(vec_minus(hitp, center)), 2);
    // a = c - (r * r);
    
    // normal = vec_minus(vec_multiply(center, a/a), hitp);
    
    
    return (normal);
}

int     ft_in_range(t_cylinder *cy, t_vec *hitp)
{
    
    return (0);
}


int     ft_cylinder_intersect(t_cylinder *cy, t_ray *ray, t_hit *hitp)
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

    double a = dot_product(dir_x_norm, dir_x_norm);
    double b = 2 * dot_product(dir_x_norm, v_x_norm);
    double c = dot_product(v_x_norm, v_x_norm) - (cy->r * cy->r);
    double discr = (b * b) - (4 * a * c);
    double t1 = 0;
    double t2 = 0;
    if (discr < 0)
        return (0);


	t1 = (-b + sqrt(discr)) / (2 * a);
	t2 = (-b - sqrt(discr)) / (2 * a);
    if (t2 < t1 && t2 > 0)
        t1 = t2;

    // if (!ft_in_range(cy, &hitp->hitpoint))
    //     return (0);
    if (t1 < hitp->nearest && t1 >= 0)
	{
        // printf("CYLINDERfound t: %lf\n", t1);
		hitp->nearest = t1;
		hitp->color = cy->colors;
		hitp->object_id = cy->id;
        hitp->hitpoint  = calc_hitpoint(ray, t1);
        hitp->normal = normalize(ft_cyl_normal(cy->r,  hitp->hitpoint, cy->coords, cy->normal));
        // if (dot_product(ray->direction, hitp->normal) < 0)
        //     hitp->normal = vec_multiply(hitp->normal, -1);
	    // hitp->normal = cy->normal;
		return (1);
	}
    
    return (0);
}