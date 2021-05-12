#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <strings.h>
#include "../headers/minirt.h"

#define HEADER_SIZE 54
#define UNUSED

void create_bmp_file_header(t_bmp_file_header *fh, int width, int height)
{

	bzero(fh, sizeof(t_bmp_file_header));
	fh->name[0] = 'B';
	fh->name[1] = 'M';
	fh->file_size = width * height * 3 + HEADER_SIZE;
	fh->offset = HEADER_SIZE;
}


void create_bmp_info_header(t_bmp_info_header *ih, int width, int height)
{
	bzero(ih, sizeof(t_bmp_info_header));
	ih->info_header_size = 40;
	ih->width = width;
	ih->height = height;
	ih->planes = 1;
	ih->bit_count = 24;
	ih->ppm_x = width * height / 20;
	ih->ppm_y = width * height / 20;
}

void write_bmp_header(int fd, t_bmp_file_header *fh, t_bmp_info_header *ih)
{
	write(fd, fh->name, 2);
	write(fd, (char*)fh + 4, 12);
	write(fd, ih, sizeof(t_bmp_info_header));
}

int	ft_put_img_to_bmp(char *file_name, t_env *env, t_3rgb *col)
{
	t_bmp_file_header *fh;
	t_bmp_info_header *ih;
	int		size;

	fh = malloc(1 * sizeof(t_bmp_file_header));
	ih = malloc(1 * sizeof(t_bmp_info_header));
	if (!fh || !ih)
		return (-1);
	size = env->res.y * env->res.x * 3;
	create_bmp_info_header(ih, env->res.x, env->res.y);
	create_bmp_file_header(fh, env->res.x, env->res.y);
	int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (!fd)
		return (-1);
	write_bmp_header(fd, fh, ih);

	if (env->filters.sepia)
		col = ft_sepia(col, env->res.x, env->res.y);
	else if (env->filters.grayscale)
		col = ft_grayscale(col, env->res.x, env->res.y);
	if (write(fd, col, size) < 0)
		ft_parse_error("ERRRROOOOOOR");
	free(fh);
	free(ih);
	close(fd);
	return (fd);
}
