#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <strings.h>
// #include "../headers/ft_structure.h"



typedef struct	s_bmp_file_header
{
    uint8_t   	name[2]; // should be "BM"
    uint32_t	file_size; // height * width
    uint16_t	bmp_def; // defaults to 0
    uint16_t	bmp_def2; // defaults to 0
    uint32_t	offset; // info + file header
}				t_bmp_file_header;


typedef struct 	s_bmp_info_header
{
	uint32_t info_header_size; // 40
	uint32_t width; // height and width of res
	uint32_t height;
	uint16_t planes; // should be 1
	uint16_t bit_count;  // 1, 4, 8,16,24 or (32)
	uint32_t compression; // 0
	uint32_t img_size; //possible zero or something?
	uint32_t ppm_x; // can be zero or set to ppmconversionfactor
	uint32_t ppm_y; // can be zero
	uint32_t color_used; // 0
	uint32_t important; // if set to zero every color is important
}				t_bmp_info_header;

void create_bmp_file_header(t_bmp_file_header *fh, int width, int height)
{

	bzero(fh, sizeof(t_bmp_file_header));
	fh->name[0] = 'B';
	fh->name[1] = 'M';
	fh->file_size = width * height * 3;
	fh->bmp_def = 0;
	fh->bmp_def2 = 0;
	fh->offset = sizeof(t_bmp_file_header) + sizeof(t_bmp_info_header);
	// printf("struct size: %lu\n", sizeof(t_bitmap_file_header));
}


void create_bmp_info_header(t_bmp_info_header *ih, int width, int height)
{
	bzero(ih, sizeof(t_bmp_info_header));
	ih->info_header_size = 40; //sizeof(t_info_header);
	ih->width = width;
	ih->height = height;
	ih->planes = 1;
	ih->bit_count = 24;
	ih->compression = 0;
	ih->img_size = (width * height * 3) + 2;
	ih->ppm_x = 9448;
	ih->ppm_y = 9448;
	ih->color_used = 0;
	ih->important = 0;
}

// int	write_bmp_header(int fd, int width, int height)
// {
// 	int		i;
// 	char	tag[2];
// 	int		header[14];

// 	i = 7;
// 	tag[0] = 'B';
// 	tag[1] = 'M';
// 	header[0] = height * width * 3;
// 	header[1] = 0;
// 	header[2] = 54;
// 	header[3] = 40;
// 	header[4] = width;
// 	header[5] = height;
// 	header[6] = 0x180001;
// 	while (i < 14)
// 	{
// 		header[i] = 0;
// 		i++;
// 	}
// 	header[0] = 58;
// 	if (write(fd, &tag, sizeof(tag)) < 0)
// 		return (-1);
// 	if (write(fd, &header, sizeof(header)) < 0)
// 		return (-1);
// 	return (1);
// }

void open_bmp_file(char *filename)
{
	t_bmp_file_header bf;
	t_bmp_info_header bi;
	FILE *fd = fopen(filename,  "rb");
	if (fd == NULL)
	{
		printf("Error opening!\n");
		return ;
	}
	// fread(bf.name, 2, 1, fd);
	// fread(&bf.size, 2 * sizeof(int), 1, fd);
	// fread(&bf.offset, sizeof(int), 1, fd);
	// fread(&bf.bmp_defaults, sizeof(int), 1, fd);
	// printf("sizeofstruct: %lu\n", sizeof(t_bitmap_file_header));
	fread(&bf, sizeof(t_bmp_file_header), 1, fd);
	fread(&bi, sizeof(t_bmp_info_header), 1, fd);
	// if (rb != sizeof(t_bitmap_file_header))
	// {
	// 	printf("Error reading!\n");
	// 	return ;	
	// }
	
	printf("\n\nName: %c%c\n", bf.name[0], bf.name[1]);
	printf("fileSize: %d\n", bf.file_size);
	printf("def: %hu\n", bf.bmp_def);
	printf("def: %hu\n", bf.bmp_def2);
	printf("ooffest: %d\n\nn", bf.offset);


	printf("Headersize: %u\n", bi.info_header_size); // should be 400
	printf("width: %u\n", bi.width); // should be 600
	printf("Height: %u\n", bi.height); // should be 400
	printf("planes: %i\n", bi.planes); // should be 400
	printf("bitcount: %u\n", bi.bit_count); // should be 400
	printf("compression: %u\n", bi.compression); // should be 400
	printf("imgsize: %u\n", bi.img_size); // should be 400
	printf("ppmx: %u\n", bi.ppm_x); // should be 400
	printf("ppmy: %u\n", bi.ppm_y); // should be 400
	printf("clrused: %u\n", bi.color_used); // should be 400
	printf("important: %u\n", bi.important); // should be 400
	// printf("bftype: %c%c\n", bf.name[0], bf.name[1]);
	// printf("size: %d\n", bf.size);
	// // printf("reserved1: %d\n", bf.bfReserved2);
	// printf("reserved2: %d\n", bf.bmp_def);
	// printf("offBits: %d\n", bf.offset);
	fclose(fd);
}

void write_bmp_header(int fd, t_bmp_file_header *fh, t_bmp_info_header *ih)
{
	// write(fd, "0", 1);
	write(fd, &fh->name, 2);
	write(fd, &fh->file_size, 4);
	write(fd, &fh->bmp_def, 2);
	write(fd, &fh->bmp_def2, 2);
	write(fd, &fh->offset, 4);
	// write(fd, "00", 2);
	// write(fd, fh, sizeof(t_bmp_file_header));
	write(fd, &ih->info_header_size, 4);
	write(fd, &ih->width, 4);
	write(fd, &ih->height, 4);
	write(fd, &ih->planes, 2);
	write(fd, &ih->bit_count, 2);
	write(fd, &ih->compression, 4);
	write(fd, &ih->img_size, 4);
	write(fd, &ih->ppm_x, 4);
	write(fd, &ih->ppm_y, 4);
	write(fd, &ih->color_used, 4);
	write(fd, &ih->important, 4);
	// write(fd, ih, sizeof(t_bmp_info_header));
}

int	create_bmp(char *file_name)
{
	t_bmp_file_header fh;
	t_bmp_info_header ih;
	int		width = 600;
	int		height = 400;
	int		size = height * width * 3;
	char	*white = malloc(size);
	memset(white, 255, size);

	create_bmp_info_header(&ih, width, height);
	create_bmp_file_header(&fh, width, height);

	int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (!fd)
		return (-1);
	write_bmp_header(fd, &fh, &ih);
	write(fd, white, size);
	// int i = 
	// if (!write(fd, white, size))
	// 	return (-1);
	close(fd);
	return (fd);
}

int main(void)
{
	create_bmp("mini.bmp");
	open_bmp_file("mini.bmp");
	return (0);
}