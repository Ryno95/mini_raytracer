/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_matrices.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/28 11:12:50 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/04/28 19:33:05 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void  ft_create_id_matrix(t_matrix3x3 *matrix)
{
    int i;
    
    if (!matrix)
        return ;
    i = 0;
    while (i < 3)
    {
        matrix->m[i][i] = 1;
        i++;
    }
}

// t_matrix4x4  ft_matrix_multi(t_matrix4x4 a, t_matrix4x4 b)
// {
//     t_matrix4x4 m;

//     int i = 0;
//     int j = 0;
//     while (i < 4)
//     {
//         j = 0;
//         while (j < 4)
//         {
//             m.m[i][j] = a.m[i][0] * b.m[0][j] + 
//                         a.m[i][1] * b.m[1][j] + 
//                         a.m[i][2] * b.m[2][j] + 
//                         a.m[i][3] * b.m[3][j];
//             j++;
//         }
//         i++;
//     }
//     return (m);
// }

t_vec     ft_vec_multi_matrix(t_matrix3x3 m, t_vec vect)
{
    t_vec ret_vec;

    ret_vec.x = m.m[0][0] * vect.x + m.m[0][1] * vect.y + m.m[0][2] * vect.z;
    ret_vec.y = m.m[1][0] * vect.x + m.m[1][1] * vect.y + m.m[1][2] * vect.z;
    ret_vec.z = m.m[2][0] * vect.x + m.m[2][1] * vect.y + m.m[2][2] * vect.z;
    return (ret_vec);
}
