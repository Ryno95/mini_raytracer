/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atof.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/05 16:19:16 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/31 15:00:22 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

float		ft_atof(char *str)
{
	float i;
	float num;
	int sign;

	sign = 1;
	i = 10;
	num = 0;
	if (!str)
		return (0);
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	while(*str && ft_isdigit(*str))
	{
		num = (num * 10) + *str - 48;
		str++;
	}
	if (*str == '.')
	{
		str++;
		while(*str && ft_isdigit(*str))
		{
			num = num + (((*str - 48) / i));
			str++;
			i *= 10;
		}
	}
	return (num * sign);
}
