/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_math_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 20:49:30 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/07 20:57:22 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float	ft_round_fl(float num, int decimals)
{
	float  rounded_nbr;
	if (decimals == 0)
		return (num);

	rounded_nbr = ((int)((num * pow(10, decimals)) + 0.5)) / pow(10, decimals);
	
	return (rounded_nbr);
}

float	ft_vec_len(t_coord coords)
{
	return(sqrt(pow((coords.x), 2) + pow((coords.y), 2) + pow((coords.z), 2)));	
}