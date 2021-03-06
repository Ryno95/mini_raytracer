/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_errors.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/06 21:48:19 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/06 21:54:25 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	ft_parse_error(char *err_desc)
{
	// usage: object, ex: camera and content, ex. colors
	printf("Error parsing %s\n", err_desc);
	exit(1);
}
