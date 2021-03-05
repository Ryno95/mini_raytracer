/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atof.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/05 16:19:16 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/05 17:02:15 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

float		ft_atof(char *str)
{
	float i;
	float num;

	i = 10;
	num = 0;
	if (!str)
		return (0);
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
	return (num);
}
