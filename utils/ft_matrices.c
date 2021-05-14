/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_matrices.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/28 11:12:50 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/13 13:09:42 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_structure.h"

t_vec	ft_vec_multi_matrix(t_matrix3x3 m, t_vec vect)
{
	t_vec	ret_vec;

	ret_vec.x = m.m[0][0] * vect.x + m.m[0][1] * vect.y + m.m[0][2] * vect.z;
	ret_vec.y = m.m[1][0] * vect.x + m.m[1][1] * vect.y + m.m[1][2] * vect.z;
	ret_vec.z = m.m[2][0] * vect.x + m.m[2][1] * vect.y + m.m[2][2] * vect.z;
	return (ret_vec);
}
