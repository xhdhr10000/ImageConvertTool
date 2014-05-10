#include "StdAfx.h"
#include "Converter.h"

int ARGB8888_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	memcpy_s(outBuffer, size, inBuffer, size);
	return size;
}

int ABGR8888_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

	while ((unsigned int)(in-*inBuffer)<size) {
		out[0] = in[2];
		out[1] = in[1];
		out[2] = in[0];
		out[3] = in[3];
		in += 4;
		out += 4;
	}

	return size;
}

int XRGB8888_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	memcpy_s(outBuffer, size, inBuffer, size);
	return size;
}

int XBGR8888_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	return ABGR8888_to_standard(inBuffer, size, outBuffer);
}

int ABGR1555_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	/* ABBBBBGG GGGRRRRR */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

	while ((unsigned int)(in-inBuffer)<size) {
		out[0] = (in[1]&0x7C)<<1;
		out[1] = ((in[1]&0x3)<<6)&((in[0]&0xE0)>>2);
		out[2] = (in[0]&0x1F)<<3;
		out[3] = ((in[1]>>7)&0x1)?0xFF:0;
		in += 2;
		out += 4;
	}

	return size*2;
}

int ARGB4444_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	/* AAAARRRR GGGGBBBB */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

	while ((unsigned int)(in-inBuffer)<size) {
		out[0] = (in[0]&0x0F)<<4;
		out[1] = in[0]&0xF0;
		out[2] = (in[1]&0x0F)<<4;
		out[3] = in[1]&0xF0;
		in += 2;
		out += 4;
	}

	return size*2;
}

int RGB565_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	/* RRRRRGGG GGGBBBBB */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

	while ((unsigned int)(in-inBuffer)<size) {
		out[0] = (in[0]&0x1F)<<3;
		out[1] = ((in[1]&0x7)<<5)&((in[0]&0x70)>>3);
		out[2] = in[1]&0xF8;
		out[3] = 0xFF;
		in += 2;
		out += 4;
	}

	return size*2;
}

int BGR565_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	/* BBBBBGGG GGGRRRRR */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

	while ((unsigned int)(in-inBuffer)<size) {
		out[0] = in[1]&0xF8;
		out[1] = ((in[1]&0x7)<<5)&((in[0]&0x70)>>3);
		out[2] = (in[0]&0x1F)<<3;
		out[3] = 0xFF;
		in += 2;
		out += 4;
	}

	return size*2;
}

int YUV420_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	return 0;
}

int TILEMODE_to_standard(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	return 0;
}




int standard_to_ARGB8888(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	memcpy_s(outBuffer, size, inBuffer, size);
	return size;
}

int standard_to_ABGR8888(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

	while ((unsigned int)(in-inBuffer)<size) {
		out[0] = in[2];
		out[1] = in[1];
		out[2] = in[0];
		out[3] = in[3];
		in += 4;
		out += 4;
	}

	return size;
}

int standard_to_XRGB8888(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	memcpy_s(outBuffer, size, inBuffer, size);
	return size;
}

int standard_to_XBGR8888(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

	while ((unsigned int)(in-inBuffer)<size) {
		out[0] = in[2];
		out[1] = in[1];
		out[2] = in[0];
		out[3] = 0xFF;
		in += 4;
		out += 4;
	}

	return size;
}

int standard_to_ABGR1555(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	/* ABBBBBGG GGGRRRRR */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

	while ((unsigned int)(in-inBuffer)<size) {
		out[1] = in[3]&0x80;
		out[1] |= ((in[0]&0xF8)>>1);
		out[1] |= ((in[1]&0xC0)>>6);
		out[0] = (in[1]&0x38)<<2;
		out[0] |= ((in[2]&0xF8)>>3);
		in += 4;
		out += 2;
	}

	return size/2;
}

int standard_to_ARGB4444(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	/* AAAARRRR GGGGBBBB */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

	while ((unsigned int)(in-inBuffer)<size) {
		out[1] = in[3]&0xF0;
		out[1] |= ((in[2]&0xF0)>>4);
		out[0] = in[1]&0xF0;
		out[0] |= ((in[0]&0xF0)>>4);
		in += 4;
		out += 2;
	}

	return size/2;
}

int standard_to_RGB565(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	/* RRRRRGGG GGGBBBBB */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

	while ((unsigned int)(in-inBuffer)<size) {
		out[1] = in[2]&0xF8;
		out[1] |= ((in[1]&0xE0)>>5);
		out[0] = ((in[1]&0x1C)<<3);
		out[0] |= ((in[0]&0xF8)>>3);
		in += 4;
		out += 2;
	}

	return size/2;
}

int standard_to_BGR565(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	/**
	 * BBBBBGGG GGGRRRRR
	 */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

	while ((unsigned int)(in-inBuffer)<size) {
		out[1] = in[0]&0xF8;
		out[1] |= ((in[1]&0xE0)>>5);
		out[0] = ((in[1]&0x1C)<<3);
		out[0] |= ((in[2]&0xF8)>>3);
		in += 4;
		out += 2;
	}

	return size/2;
}

int standard_to_YUV420(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	return 0;
}

int standard_to_TILEMODE(unsigned char *inBuffer, unsigned int size, unsigned char *outBuffer)
{
	return 0;
}


int output_ARGB8888(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path)
{
	return output_BMP(buffer, x, y, 32, ARGB8888, path);
}

int output_ABGR8888(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path)
{
	return output_BMP(buffer, x, y, 32, ABGR8888, path);
}

int output_XRGB8888(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path)
{
	return output_BMP(buffer, x, y, 32, XRGB8888, path);
}

int output_XBGR8888(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path)
{
	return output_BMP(buffer, x, y, 32, XBGR8888, path);
}

int output_ABGR1555(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path)
{
	return output_BMP(buffer, x, y, 16, ABGR1555, path);
}

int output_ARGB4444(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path)
{
	return output_BMP(buffer, x, y, 16, ARGB4444, path);
}

int output_RGB565(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path)
{
	return output_BMP(buffer, x, y, 16, RGB565, path);
}

int output_BGR565(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path)
{
	return output_BMP(buffer, x, y, 16, BGR565, path);
}

int output_YUV420(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path)
{
	FILE *f;

	_tfopen_s(&f, path, _T("wb"));
	if (f == NULL) return -1;
	fwrite(buffer, x*y*3/2, 1, f);
	fclose(f);

	return 0;
}

int output_TILEMODE(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path)
{
	return 0;
}

int output_BMP_Header(unsigned int x, unsigned int y, unsigned int bpp, Formats format, FILE *f)
{
	bmp_header header;
	dib_header dib;
	palette pal;

	memset(&header, 0, sizeof(header));
	memset(&dib, 0, sizeof(dib));
	memset(&pal, 0, sizeof(pal));

	dib.header_size = sizeof(dib_header);
	dib.bitmap_width = x;
	dib.bitmap_height = y;
	dib.num_color_planes = 1;
	dib.bits_per_pixel = bpp;
	dib.compression = BI_RGB;
	dib.image_size = x*y*bpp/8;
	dib.horizontal_resolution = 0xB13;
	dib.vertical_resolution = 0xB13;

	header.magic_number = 0x4d42;
	header.offset = sizeof(bmp_header)+sizeof(dib_header)+((bpp==16)?sizeof(palette):0);
	header.file_size = dib.image_size+header.offset;

	if (bpp == 16) {
		switch (format) {
		case ABGR1555:
			/* ABBBBBGG GGGRRRRR */
			pal.alpha	= 0x8000;
			pal.red		= 0x1F;
			pal.green	= 0x3E0;
			pal.blue	= 0x7C00;
			break;
		case ARGB4444:
			/* AAAARRRR GGGGBBBB */
			pal.alpha	= 0xF000;
			pal.red		= 0xF00;
			pal.green	= 0xF0;
			pal.blue	= 0xF;
			break;
		case RGB565:
			/* RRRRRGGG GGGBBBBB */
			pal.alpha	= 0;
			pal.red		= 0xF800;
			pal.green	= 0x7E0;
			pal.blue	= 0x1F;
			break;
		case BGR565:
			/* BBBBBGGG GGGRRRRR */
			pal.alpha	= 0;
			pal.red		= 0x1F;
			pal.green	= 0x7E0;
			pal.blue	= 0xF800;
			break;
		}
	}

	fwrite(&header, sizeof(header), 1, f);
	fwrite(&dib, sizeof(dib), 1, f);
	if (bpp == 16) fwrite(&pal, sizeof(pal), 1, f);

	return 0;
}

int output_BMP(unsigned char *buffer, unsigned int x, unsigned int y,
			   unsigned int bpp, Formats format, TCHAR *path)
{
	FILE *f;

	_tfopen_s(&f, path, _T("wb"));
	if (f == NULL) return -1;
	if (output_BMP_Header(x, y, bpp, format, f)) return -1;

	fwrite(buffer, x*y*bpp/8, 1, f);
	fclose(f);

	return 0;
}