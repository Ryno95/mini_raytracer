/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atof.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/05 16:19:16 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/14 18:10:05 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

float	ft_get_float(char *str, float num)
{
	int i;

	i = 10;
	while (*str && ft_isdigit(*str))
	{
		num = (num * 10) + *str - 48;
		str++;
	}
	if (*str == '.')
	{
		str++;
		printf("str: %s\n", str);
		while (*str && ft_isdigit(*str))
		{
			num = num + (((*str - 48) / i));
			str++;
			i *= 10;
			printf("num: %f\n",num);
		}
	}
	return (num);
}

float	ft_atof(char *str)
{
	float	num;
	int		sign;

	sign = 1;
	num = 0;
	if (!str)
		return (0);
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	num = ft_get_float(&(*str), num);
	return (num * sign);
}
