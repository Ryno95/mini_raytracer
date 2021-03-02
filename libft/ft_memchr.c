/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:07:22 by rmeiboom      #+#    #+#                 */
/*   Updated: 2020/11/14 14:21:23 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*cursor;
	char	*str;
	size_t	i;

	str = (char*)s;
	cursor = NULL;
	i = 0;
	while (i < n)
	{
		if (str[i] == c)
		{
			cursor = &str[i];
			break ;
		}
		i++;
	}
	return (cursor);
}
