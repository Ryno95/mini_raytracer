/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_output_to_bmp.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/14 17:47:45 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/14 17:48:01 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "../headers/minirt.h"
#include "../headers/ft_defines.h"

void create_bmp_file_header(t_bmp_file_header *fh, int width, int height)
{
	ft_bzero(fh, sizeof(t_bmp_file_header));
	fh->name[0] = 'B';
	fh->name[1] = 'M';
	fh->file_size = width * height * 3 + ALL_HEADER_SIZE;
	fh->offset = ALL_HEADER_SIZE;
}


void create_bmp_info_header(t_bmp_info_header *ih, int width, int height)
{
	ft_bzero(ih, sizeof(t_bmp_info_header));
	ih->info_header_size = INFO_HEADER_SIZE;
	ih->width = width;
	ih->height = height;
	ih->planes = PLANES_DEF;
	ih->bit_count = BITCOUNT;
}

int write_bmp_header(int fd, int width, int height)
{
	t_bmp_file_header *fh;
	t_bmp_info_header *ih;

	fh = malloc(1 * sizeof(t_bmp_file_header));
	ih = malloc(1 * sizeof(t_bmp_info_header));
	if (!fh || !ih)
		return (0);
	create_bmp_info_header(ih, width, height);
	create_bmp_file_header(fh, width, height);	
	if (write(fd, fh->name, BMP_NAME_BYTES) != BMP_NAME_BYTES)
		return (0);
	if (write(fd, (char*)fh + 4, FILE_HEADER_SIZE - BMP_NAME_BYTES) != 12)
		return (0);
	if(write(fd, ih, sizeof(t_bmp_info_header)) != sizeof(t_bmp_info_header))
		return (0);
	free(fh);
	free(ih);
	return (1);
}

int	ft_put_img_to_bmp(char *file_name, t_env *env, t_3rgb *col)
{
	int		size;
	int		fd;

	size = env->res.y * env->res.x * 3;
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, FILE_PERMISSIONS);
	if (!fd)
		return (0);
	write_bmp_header(fd, env->res.x, env->res.y);
	if (env->filters.sepia)
		col = ft_sepia(col, env->res.x, env->res.y);
	else if (env->filters.grayscale)
		col = ft_grayscale(col, env->res.x, env->res.y);
	if (write(fd, col, size) < 0)
		ft_exit(env, "Couldn't write complete images");
	close(fd);
	return (fd);
}
