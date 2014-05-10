#pragma once

enum Formats {
	ARGB8888 = 0,
	ABGR8888,
	XRGB8888,
	XBGR8888,
	ABGR1555,
	ARGB4444,
	RGB565,
	BGR565,
	YUV420,
	TILEMODE,
};

#define PACKED
#pragma pack(push,1)

struct bmp_header {
	unsigned short  magic_number;
	unsigned int    file_size;
	unsigned short  reserved[2];
	unsigned int    offset;
}PACKED;

#pragma pack(pop)
#undef PACKED

struct dib_header {
	unsigned int    header_size;
	int             bitmap_width;
	int             bitmap_height;
	unsigned short  num_color_planes;
	unsigned short  bits_per_pixel;
	unsigned int    compression;
	unsigned int    image_size;
	int             horizontal_resolution;  //pixel per meter
	int             vertical_resolution;    //pixel per meter
	unsigned int    num_colors_in_palette;
	unsigned int    num_important_colors;
};

struct palette {
	int red;
	int green;
	int blue;
	int alpha;
};


typedef int (*funcToStandard)(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
typedef int (*funcFromStandard)(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
typedef int (*funcOutput)(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path);

int ARGB8888_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int ABGR8888_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int XRGB8888_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int XBGR8888_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int ABGR1555_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int ARGB4444_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int RGB565_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int BGR565_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int YUV420_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int TILEMODE_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);

int standard_to_ARGB8888(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int standard_to_ABGR8888(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int standard_to_XRGB8888(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int standard_to_XBGR8888(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int standard_to_ABGR1555(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int standard_to_ARGB4444(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int standard_to_RGB565(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int standard_to_BGR565(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int standard_to_YUV420(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);
int standard_to_TILEMODE(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer);

int output_ARGB8888(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path);
int output_ABGR8888(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path);
int output_XRGB8888(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path);
int output_XBGR8888(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path);
int output_ABGR1555(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path);
int output_ARGB4444(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path);
int output_RGB565(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path);
int output_BGR565(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path);
int output_YUV420(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path);
int output_TILEMODE(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path);

int output_BMP_Header(unsigned int x, unsigned int y, unsigned int bpp, Formats format, FILE *f);
int output_BMP(unsigned char *buffer, unsigned int x, unsigned int y,
			   unsigned int bpp, Formats format, TCHAR *path);