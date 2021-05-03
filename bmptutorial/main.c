#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
typedef struct s_BITMAP_Header {
	char name[2]; // this should be equal to BM
	unsigned int size; // should be a variable of size four, sizeof(int) = 4
	u_int16_t	bmp_defaults1; // set to 0
	u_int16_t	bmp_defaults2; // set to 0
	unsigned int offset; // offset from where the image starts in file
} BITMAP_Header;



typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

/**
 * BITMAPFILEHEADER
 *
 * The BITMAPFILEHEADER structure contains information about the type, size,
 * and layout of a file that contains a DIB [device-independent bitmap].
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/dd183374(VS.85).aspx.
 */
typedef struct
{
    char   		  	name[2];
    unsigned int  	size;
    int				bmp_def;
    unsigned int	offset;
} __attribute__((__packed__))
BITMAPFILEHEADER;

/**
 * BITMAPINFOHEADER
 *
 * The BITMAPINFOHEADER structure contains information about the
 * dimensions and color format of a DIB [device-independent bitmap].
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/dd183376(VS.85).aspx.
 */
typedef struct
{
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} __attribute__((__packed__))
BITMAPINFOHEADER;

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
}				t_info_header;

void open_bmp_file(void)
{
	BITMAPFILEHEADER bf;
	t_info_header bi;
	FILE *fd = fopen("stadium.bmp", "rb");
	if (fd == NULL)
	{
		printf("Error opening!\n");
		return ;
	}
	// fread(bf.name, 2, 1, fd);
	// fread(&bf.size, 2 * sizeof(int), 1, fd);
	// fread(&bf.offset, sizeof(int), 1, fd);
	// fread(&bf.bmp_defaults, sizeof(int), 1, fd);
	// printf("sizeofstruct: %lu\n", sizeof(BITMAPFILEHEADER));
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fd);
	fread(&bi, sizeof(t_info_header), 1, fd);
	// if (rb != sizeof(BITMAPFILEHEADER))
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

int create_bmp_file_header(int width, int height)
{
	BITMAPFILEHEADER fh;

	fh.name[0] = 'B';
	fh.name[1] = 'M';
	fh.bmp_def = 0;
	fh.size = width * height + sizeof(BITMAPFILEHEADER);
	fh.offset = sizeof(BITMAPFILEHEADER);
	printf("struct size: %lu\n", sizeof(BITMAPFILEHEADER));
}

int create_bmp_info_header(void)
{
	uint32_t ih_size;
}

int main (void)
{
	open_bmp_file();
	// create_bmp_header(100, 100);
	return (0);
}