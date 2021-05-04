#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <strings.h>

typedef struct s_bitmap_file_header
{
    char   		  	name[2]; // should be "BM"
    unsigned int  	size; // height * width
    int				bmp_def; // defaults to 0
    unsigned int	offset; // info + file header
} __attribute__((__packed__))
t_bitmap_file_header;


typedef struct 	s_info_header
{
	uint32_t info_header_size; // 40
	uint32_t width; // height and width of res
	uint32_t height;
	uint16_t planes; // should be 1
	uint16_t bit_count;  // 1, 4, (8), 16,24 or 32
	uint32_t compression; // 0
	uint32_t img_size; //possible zero or something?
	int		 ppm_x; // can be zero or set to ppmconversionfactor
	int		 ppm_y; // can be zero
	uint32_t color_used; // 0
	uint32_t important; // if set to zero every color is important
} __attribute__((__packed__)) t_info_header;

void open_bmp_file(char *filename)
{
	t_bitmap_file_header bf;
	t_info_header bi;
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
	fread(&bf, sizeof(t_bitmap_file_header) + 2 , 1, fd);
	fread(&bi, sizeof(t_info_header), 1, fd);
	// if (rb != sizeof(t_bitmap_file_header))
	// {
	// 	printf("Error reading!\n");
	// 	return ;	
	// }
	printf("width: %u\n", bi.width); // should be 600
	printf("Height: %u\n", bi.img_size); // should be 400
	// printf("bftype: %c%c\n", bf.name[0], bf.name[1]);
	// printf("size: %d\n", bf.size);
	// // printf("reserved1: %d\n", bf.bfReserved2);
	// printf("reserved2: %d\n", bf.bmp_def);
	// printf("offBits: %d\n", bf.offset);
	fclose(fd);
}

t_bitmap_file_header create_bmp_file_header(int width, int height)
{
	t_bitmap_file_header fh;

	bzero(&fh, sizeof(t_bitmap_file_header));
	fh.name[0] = 'B';
	fh.name[1] = 'M';
	fh.bmp_def = 0;
	fh.size = width * height * 3;
	fh.offset = sizeof(t_bitmap_file_header) + sizeof(t_info_header);
	return (fh);
	// printf("struct size: %lu\n", sizeof(t_bitmap_file_header));
}

t_info_header create_bmp_info_header(int width, int height)
{
	t_info_header ih;
	bzero(&ih, sizeof(t_info_header));
	ih.info_header_size = 40; //sizeof(t_info_header);
	ih.width = width;
	ih.height = height;
	ih.planes = 1;
	ih.bit_count = 16;
	ih.compression = 0;
	ih.img_size = 0;
	ih.ppm_x = 0;
	ih.ppm_y = 0;
	ih.color_used = 0;
	ih.important = 0;
}

int main (void)
{
	int heigth = 400;
	int width = 600;
	t_bitmap_file_header fh = create_bmp_file_header(width, heigth);
	t_info_header ih = create_bmp_info_header(width, heigth);
	int fd = open("mybmp.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (!fd)
		printf("errror opening");
	write(fd, &fh, sizeof(t_bitmap_file_header));
	write(fd, &ih, sizeof(t_info_header));
	close(fd);


	// while()
	open_bmp_file("mybmp.bmp");
	// create_bmp_header(100, 100);
	return (0);
}