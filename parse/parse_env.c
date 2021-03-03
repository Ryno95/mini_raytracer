/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 13:31:58 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/03/03 13:40:06 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int     parse_res(char *line, t_res *res)
{
    char **split_str;

    split_str = ft_split_set(line, " \t"); //split by whitespace !!!TODO!!!
}