/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_defines.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 18:15:59 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/14 16:22:09 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFINES_H
# define FT_DEFINES_H

# define ALL_HEADER_SIZE 54
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40
# define PLANES_DEF 1
# define BITCOUNT 24
# define BMP_NAME_BYTES 2
# define FILE_PERMISSIONS 0664

# define MAX_WIDTH 2560
# define MAX_HEIGHT 1440

# define ESC 53
# define TAB 48

# define NUMBER_OF_THREADS 4
# define FILE_EXTENSION ".rt\0"

# define ID_RES "R\0"
# define ID_AMB_LIGHT "A\0"
# define ID_CAMERA "c\0"
# define ID_LIGHT "l\0"

# define ID_SPHERE "sp\0"
# define ID_PLANE "pl\0"
# define ID_SQUARE "sq\0"
# define ID_CYLINDER "cy\0"
# define ID_TRIANGLE "tr\0"

#endif