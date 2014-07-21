#include "StdAfx.h"
#include "Converter.h"

#define T_X	8
#define T_Y	4

int RGB888_to_standard(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

#if 1
	unsigned int i, j;
	for (i=y-1; (int)i>=0; i--) {
		for (j=0; j<x; j++) {
			out[(i*x+j)*4+0] = in[0];
			out[(i*x+j)*4+1] = in[1];
			out[(i*x+j)*4+2] = in[2];
			out[(i*x+j)*4+3] = 0xFF;
			in += 3;
		}
		if (x*3%4 != 0) in += 4-x*3%4;
	}
#else
	while ((unsigned int)(in-inBuffer)<size) {
		out[0] = in[0];
		out[1] = in[1];
		out[2] = in[2];
		out[3] = 0xFF;
		in += 3;
		out += 4;
	}
#endif

	return size*4/3;
}

int ARGB8888_to_standard(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
#if 1
	unsigned char *in, *out;
	unsigned int i, j;

	in = inBuffer;
	out = outBuffer;

	for (i=y-1; (int)i>=0; i--)
		for (j=0; j<x; j++) {
			out[(i*x+j)*4+0] = in[0];
			out[(i*x+j)*4+1] = in[1];
			out[(i*x+j)*4+2] = in[2];
			out[(i*x+j)*4+3] = in[3];
			in += 4;
		}
#else
	memcpy_s(outBuffer, size, inBuffer, size);
#endif
	return size;
}

int ABGR8888_to_standard(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

#if 1
	unsigned int i, j;
	for (i=y-1; (int)i>=0; i--)
		for (j=0; j<x; j++) {
			out[(i*x+j)*4+0] = in[2];
			out[(i*x+j)*4+1] = in[1];
			out[(i*x+j)*4+2] = in[0];
			out[(i*x+j)*4+3] = in[3];
			in += 4;
		}
#else
	while ((unsigned int)(in-inBuffer)<size) {
		out[0] = in[2];
		out[1] = in[1];
		out[2] = in[0];
		out[3] = in[3];
		in += 4;
		out += 4;
	}
#endif

	return size;
}

int XRGB8888_to_standard(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	ARGB8888_to_standard(inBuffer, size, x, y, outBuffer);
	return size;
}

int XBGR8888_to_standard(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	return ABGR8888_to_standard(inBuffer, size, x, y, outBuffer);
}

int ABGR1555_to_standard(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	/* ABBBBBGG GGGRRRRR */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

#if 1
	unsigned int i, j;
	for (i=y-1; (int)i>=0; i--) {
		for (j=0; j<x; j++) {
			out[(i*x+j)*4+0] = (in[1]&0x7C)<<1;
			out[(i*x+j)*4+1] = ((in[1]&0x3)<<6)|((in[0]&0xE0)>>2);
			out[(i*x+j)*4+2] = (in[0]&0x1F)<<3;
			out[(i*x+j)*4+3] = ((in[1]>>7)&0x1)?0xFF:0;
			in += 2;
		}
		if (x*2%4 != 0) in += 4-x*2%4;
	}
#else
	while ((unsigned int)(in-inBuffer)<size) {
		out[0] = (in[1]&0x7C)<<1;
		out[1] = ((in[1]&0x3)<<6)|((in[0]&0xE0)>>2);
		out[2] = (in[0]&0x1F)<<3;
		out[3] = ((in[1]>>7)&0x1)?0xFF:0;
		in += 2;
		out += 4;
	}
#endif

	return size*2;
}

int RGBA5551_to_standard(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	/* RRRRRGGG GGBBBBBA */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

	unsigned int i, j;
	for (i=y-1; (int)i>=0; i--) {
		for (j=0; j<x; j++) {
			out[(i*x+j)*4+0] = (in[0]&0x3E)<<2;
			out[(i*x+j)*4+1] = ((in[1]&0x7)<<5)|((in[0]&0xc0)>>3);
			out[(i*x+j)*4+2] = in[1]&0xF8;
			out[(i*x+j)*4+3] = (in[0]&0x1)?0xFF:0;
			in += 2;
		}
		if (x*2%4 != 0) in += 4-x*2%4;
	}

	return size*2;
}

int ARGB4444_to_standard(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	/* AAAARRRR GGGGBBBB */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

#if 1
	unsigned int i, j;
	for (i=y-1; (int)i>=0; i--) {
		for (j=0; j<x; j++) {
			out[(i*x+j)*4+0] = (in[0]&0x0F)<<4;
			out[(i*x+j)*4+1] = in[0]&0xF0;
			out[(i*x+j)*4+2] = (in[1]&0x0F)<<4;
			out[(i*x+j)*4+3] = in[1]&0xF0;
			in += 2;
		}
		if (x*2%4 != 0) in += 4-x*2%4;
	}
#else
	while ((unsigned int)(in-inBuffer)<size) {
		out[0] = (in[0]&0x0F)<<4;
		out[1] = in[0]&0xF0;
		out[2] = (in[1]&0x0F)<<4;
		out[3] = in[1]&0xF0;
		in += 2;
		out += 4;
	}
#endif

	return size*2;
}

int RGB565_to_standard(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	/* RRRRRGGG GGGBBBBB */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

#if 1
	unsigned int i, j;
	for (i=y-1; (int)i>=0; i--) {
		for (j=0; j<x; j++) {
			out[(i*x+j)*4+0] = (in[0]&0x1F)<<3;
			out[(i*x+j)*4+1] = ((in[1]&0x7)<<5)|((in[0]&0x70)>>3);
			out[(i*x+j)*4+2] = in[1]&0xF8;
			out[(i*x+j)*4+3] = 0xFF;
			in += 2;
		}
		if (x*2%4 != 0) in += 4-x*2%4;
	}
#else
	while ((unsigned int)(in-inBuffer)<size) {
		out[0] = (in[0]&0x1F)<<3;
		out[1] = ((in[1]&0x7)<<5)|((in[0]&0x70)>>3);
		out[2] = in[1]&0xF8;
		out[3] = 0xFF;
		in += 2;
		out += 4;
	}
#endif

	return size*2;
}

int BGR565_to_standard(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	/* BBBBBGGG GGGRRRRR */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

#if 1
	unsigned int i, j;
	for (i=y-1; (int)i>=0; i--) {
		for (j=0; j<x; j++) {
			out[(i*x+j)*4+0] = in[1]&0xF8;
			out[(i*x+j)*4+1] = ((in[1]&0x7)<<5)|((in[0]&0x70)>>3);
			out[(i*x+j)*4+2] = (in[0]&0x1F)<<3;
			out[(i*x+j)*4+3] = 0xFF;
			in += 2;
		}
		if (x*2%4 != 0) in += 4-x*2%4;
	}
#else
	while ((unsigned int)(in-inBuffer)<size) {
		out[0] = in[1]&0xF8;
		out[1] = ((in[1]&0x7)<<5)|((in[0]&0x70)>>3);
		out[2] = (in[0]&0x1F)<<3;
		out[3] = 0xFF;
		in += 2;
		out += 4;
	}
#endif

	return size*2;
}

int YUV420_to_standard(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	//BT601 -> RGB[0,219]
	//double matrix[3][3] = {
	//	{256, 0, 350.901}, {256, -86.132, -178.738}, {256, 443.506, 0} };
	//full range BT601 -> RGB[0,255]
	//double matrix[3][3] = {
	//	{256, 0, 357.510}, {256, -87.755, -182.105}, {256, 451.860, 0} };
	//BT601 -> RGB[0,255]
	double matrix[3][3] = {
		{298.082, 0, 408.583}, {298.082, -100.291, -208.120}, {298.082, 516.411, 0}	};
	double minus[3] = {16, 128, 128};
	int uIndex = x*y;
	int vIndex = x*y*5/4;
	unsigned int i, j;
	int temp = 0;

	for (i=0; i<y; i++) {
		for (j=0; j<x; j++) {
			// Red
			if (0) //planar
				temp = (int)(
					(matrix[0][0]*(inBuffer[i*x+j]-minus[0])) +
					(matrix[0][1]*(inBuffer[uIndex+(i/2)*(x/2)+j/2]-minus[1])) +
					(matrix[0][2]*(inBuffer[vIndex+(i/2)*(x/2)+j/2]-minus[2])) )/256;
			else //semi-planar
				temp = (int)(
					(matrix[0][0]*(inBuffer[i*x+j]-minus[0])) +
					(matrix[0][1]*(inBuffer[uIndex+((i/2)*(x/2)+j/2)*2]-minus[1])) +
					(matrix[0][2]*(inBuffer[uIndex+((i/2)*(x/2)+j/2)*2+1]-minus[2])) )/256;
			outBuffer[(i*x+j)*4+2] = (unsigned char)((temp < 0) ? 0 : ((temp > 255) ? 255 : temp));

			// Green
			if (0) //planar
				temp = (int)(
					(matrix[1][0]*(inBuffer[i*x+j]-minus[0])) +
					(matrix[1][1]*(inBuffer[uIndex+(i/2)*(x/2)+j/2]-minus[1])) +
					(matrix[1][2]*(inBuffer[vIndex+(i/2)*(x/2)+j/2]-minus[2])) )/256;
			else //semi-planar
				temp = (int)(
					(matrix[1][0]*(inBuffer[i*x+j]-minus[0])) +
					(matrix[1][1]*(inBuffer[uIndex+((i/2)*(x/2)+j/2)*2]-minus[1])) +
					(matrix[1][2]*(inBuffer[uIndex+((i/2)*(x/2)+j/2)*2+1]-minus[2])) )/256;
			outBuffer[(i*x+j)*4+1] = (unsigned char)((temp < 0) ? 0 : ((temp > 255) ? 255 : temp));

			// Blue
			if (0) //planar
				temp = (int)(
					(matrix[2][0]*(inBuffer[i*x+j]-minus[0])) +
					(matrix[2][1]*(inBuffer[uIndex+(i/2)*(x/2)+j/2]-minus[1])) +
					(matrix[2][2]*(inBuffer[vIndex+(i/2)*(x/2)+j/2]-minus[2])) )/256;
			else //semi-planar
				temp = (int)(
					(matrix[2][0]*(inBuffer[i*x+j]-minus[0])) +
					(matrix[2][1]*(inBuffer[uIndex+((i/2)*(x/2)+j/2)*2]-minus[1])) +
					(matrix[2][2]*(inBuffer[uIndex+((i/2)*(x/2)+j/2)*2+1]-minus[2])) )/256;
			outBuffer[(i*x+j)*4+0] = (unsigned char)((temp < 0) ? 0 : ((temp > 255) ? 255 : temp));
		}
	}

	return x*y*4;
}

int TILEMODE_to_standard(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	unsigned char *yuvBuffer = NULL;
	unsigned int i, j, k, l;
	int ret = 0;
	int uIndex = x*y;
	int vIndex = x*y*5/4;
	unsigned char *in;

	yuvBuffer = (unsigned char*)malloc(sizeof(unsigned char)*size);
	if (!yuvBuffer) return 0;
	in = inBuffer;
	// Y
	for (i=0; i<y; i+=T_Y)
		for (j=0; j<x; j+=T_X)
			for (k=0; k<T_Y; k++)
				for (l=0; l<T_X; l++)
					yuvBuffer[(i+k)*x+j+l] = *in++;
	// UV
	for (i=0; i<y/2; i+=T_Y) {
		for (j=0; j<x; j+=T_X) {
			for (k=0; k<T_Y; k++) {
				for (l=0; l<T_X/2; l++) {
					yuvBuffer[uIndex + (i+k)*x + j + l*2] = *in++;
					yuvBuffer[uIndex + (i+k)*x + j + l*2 +1] = *in++;
				}
			}
		}
	}

	ret = YUV420_to_standard(yuvBuffer, size, x, y, outBuffer);
	free(yuvBuffer);

	return ret;
}



int standard_to_RGB888(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

#if 1
	unsigned int i, j;
	for (i=0; i<y; i++) {
		for (j=0; j<x; j++) {
			out[0] = in[(i*x+j)*4+0];
			out[1] = in[(i*x+j)*4+1];
			out[2] = in[(i*x+j)*4+2];
			out += 3;
		}
		if (x*3%4 != 0) out += 4-x*3%4;
	}
#else
	while ((unsigned int)(in-inBuffer)<size) {
		out[0] = in[0];
		out[1] = in[1];
		out[2] = in[2];
		in += 4;
		out += 3;
	}
#endif

	return size*3/4;
}

int standard_to_ARGB8888(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	memcpy_s(outBuffer, size, inBuffer, size);
	return size;
}

int standard_to_ABGR8888(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
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

int standard_to_XRGB8888(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	memcpy_s(outBuffer, size, inBuffer, size);
	return size;
}

int standard_to_XBGR8888(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
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

int standard_to_ABGR1555(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	/* ABBBBBGG GGGRRRRR */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

#if 1
	unsigned int i, j;
	for (i=0; i<y; i++) {
		for (j=0; j<x; j++) {
			out[1] = in[(i*x+j)*4+3]&0x80;
			out[1] |= ((in[(i*x+j)*4+0]&0xF8)>>1);
			out[1] |= ((in[(i*x+j)*4+1]&0xC0)>>6);
			out[0] = (in[(i*x+j)*4+1]&0x38)<<2;
			out[0] |= ((in[(i*x+j)*4+2]&0xF8)>>3);
			out += 2;
		}
		if (x*2%4 != 0) out += 4-x*2%4;
	}
#else
	while ((unsigned int)(in-inBuffer)<size) {
		out[1] = in[3]&0x80;
		out[1] |= ((in[0]&0xF8)>>1);
		out[1] |= ((in[1]&0xC0)>>6);
		out[0] = (in[1]&0x38)<<2;
		out[0] |= ((in[2]&0xF8)>>3);
		in += 4;
		out += 2;
	}
#endif

	return size/2;
}

int standard_to_RGBA5551(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	/* RRRRRGGG GGBBBBBA */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

	unsigned int i, j;
	for (i=0; i<y; i++) {
		for (j=0; j<x; j++) {
			out[0] = in[(i*x+j)*4+3]&0x1;
			out[0] |= ((in[(i*x+j)*4+0]&0xF8)>>2);
			out[0] |= ((in[(i*x+j)*4+1]&0x18)<<3);
			out[1] = (in[(i*x+j)*4+1]&0xE0)>>5;
			out[1] |= (in[(i*x+j)*4+2]&0xF8);
			out += 2;
		}
		if (x*2%4 != 0) out += 4-x*2%4;
	}

	return size/2;
}

int standard_to_ARGB4444(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	/* AAAARRRR GGGGBBBB */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

#if 1
	unsigned int i, j;
	for (i=0; i<y; i++) {
		for (j=0; j<x; j++) {
			out[1] = in[(i*x+j)*4+3]&0xF0;
			out[1] |= ((in[(i*x+j)*4+2]&0xF0)>>4);
			out[0] = in[(i*x+j)*4+1]&0xF0;
			out[0] |= ((in[(i*x+j)*4+0]&0xF0)>>4);
			out += 2;
		}
		if (x*2%4 != 0) out += 4-x*2%4;
	}
#else
	while ((unsigned int)(in-inBuffer)<size) {
		out[1] = in[3]&0xF0;
		out[1] |= ((in[2]&0xF0)>>4);
		out[0] = in[1]&0xF0;
		out[0] |= ((in[0]&0xF0)>>4);
		in += 4;
		out += 2;
	}
#endif

	return size/2;
}

int standard_to_RGB565(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	/* RRRRRGGG GGGBBBBB */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

#if 1
	unsigned int i, j;
	for (i=0; i<y; i++) {
		for (j=0; j<x; j++) {
			out[1] = in[(i*x+j)*4+2]&0xF8;
			out[1] |= ((in[(i*x+j)*4+1]&0xE0)>>5);
			out[0] = ((in[(i*x+j)*4+1]&0x1C)<<3);
			out[0] |= ((in[(i*x+j)*4+0]&0xF8)>>3);
			out += 2;
		}
		if (x*2%4 != 0) out += 4-x*2%4;
	}
#else
	while ((unsigned int)(in-inBuffer)<size) {
		out[1] = in[2]&0xF8;
		out[1] |= ((in[1]&0xE0)>>5);
		out[0] = ((in[1]&0x1C)<<3);
		out[0] |= ((in[0]&0xF8)>>3);
		in += 4;
		out += 2;
	}
#endif

	return size/2;
}

int standard_to_BGR565(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	/**
	 * BBBBBGGG GGGRRRRR
	 */
	unsigned char *in, *out;

	in = inBuffer;
	out = outBuffer;

#if 1
	unsigned int i, j;
	for (i=0; i<y; i++) {
		for (j=0; j<x; j++) {
			out[1] = in[(i*x+j)*4+0]&0xF8;
			out[1] |= ((in[(i*x+j)*4+1]&0xE0)>>5);
			out[0] = ((in[(i*x+j)*4+1]&0x1C)<<3);
			out[0] |= ((in[(i*x+j)*4+2]&0xF8)>>3);
			out += 2;
		}
		if (x*2%4 != 0) out += 4-x*2%4;
	}
#else
	while ((unsigned int)(in-inBuffer)<size) {
		out[1] = in[0]&0xF8;
		out[1] |= ((in[1]&0xE0)>>5);
		out[0] = ((in[1]&0x1C)<<3);
		out[0] |= ((in[2]&0xF8)>>3);
		in += 4;
		out += 2;
	}
#endif

	return size/2;
}

int standard_to_YUV420(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	//RGB[0,255] -> fullrange BT.601
	//double matrix[3][3] = {
	//	{0.299, 0.587, 0.114}, {-0.169, -0.333, 0.502}, {0.502, -0.420, -0.082} };
	//RGB[0,255] -> BT.601
	double matrix[3][3] = {
		{0.257, 0.504, 0.098}, {-0.148, -0.291, 0.439}, {0.439, -0.368, -0.071} };
	double plus[3] = {16, 128, 128};
	int uIndex = x*y;
	int vIndex = x*y*5/4;
	unsigned int temp = 0, i, j;
	int *uBuffer, *vBuffer;

	uBuffer = (int*)malloc(sizeof(int)*x*y);
	if (!uBuffer) return 0;
	vBuffer = (int*)malloc(sizeof(int)*x*y);
	if (!vBuffer) {
		free(uBuffer);
		return 0;
	}
	memset(uBuffer, 0, sizeof(int)*x*y);
	memset(vBuffer, 0, sizeof(int)*x*y);
	for (i=0; i<y; i++) {
		for (j=0; j<x; j++) {
			// Y
			temp = (int)(
				(matrix[0][0]*inBuffer[(i*x+j)*4+2]) +
				(matrix[0][1]*inBuffer[(i*x+j)*4+1]) +
				(matrix[0][2]*inBuffer[(i*x+j)*4+0]) + plus[0]);
			outBuffer[i*x+j] = (unsigned char)temp;

			// U
			temp = (int)(
				(matrix[1][0]*inBuffer[(i*x+j)*4+2]) +
				(matrix[1][1]*inBuffer[(i*x+j)*4+1]) +
				(matrix[1][2]*inBuffer[(i*x+j)*4+0]) + plus[1]);
			uBuffer[i*x+j] += temp;

			// V
			temp = (int)(
				(matrix[2][0]*inBuffer[(i*x+j)*4+2]) +
				(matrix[2][1]*inBuffer[(i*x+j)*4+1]) +
				(matrix[2][2]*inBuffer[(i*x+j)*4+0]) + plus[2]);
			vBuffer[i*x+j] += temp;
		}
	}

	// convert 444 to 420
	for (i=0; i<y; i+=2) {
		for (j=0; j<x; j+=2) {
			if (0) { //planar
				outBuffer[uIndex+(i*(x/2)+j)/2] = (unsigned char)
					((uBuffer[i*x+j]+uBuffer[i*x+j+1]+uBuffer[(i+1)*x+j]+uBuffer[(i+1)*x+j+1])/4);
				outBuffer[vIndex+(i*(x/2)+j)/2] = (unsigned char)
					((vBuffer[i*x+j]+vBuffer[i*x+j+1]+vBuffer[(i+1)*x+j]+vBuffer[(i+1)*x+j+1])/4);
			} else { //semi-planar
				outBuffer[uIndex+i*(x/2)+j] = (unsigned char)
					((uBuffer[i*x+j]+uBuffer[i*x+j+1]+uBuffer[(i+1)*x+j]+uBuffer[(i+1)*x+j+1])/4);
				outBuffer[uIndex+i*(x/2)+j+1] = (unsigned char)
					((vBuffer[i*x+j]+vBuffer[i*x+j+1]+vBuffer[(i+1)*x+j]+vBuffer[(i+1)*x+j+1])/4);
			}
		}
	}
	free(uBuffer);
	free(vBuffer);

	return x*y*3/2;
}

int standard_to_TILEMODE(unsigned char *inBuffer, unsigned int size,
	unsigned int x, unsigned int y,
	unsigned char *outBuffer)
{
	unsigned char *yuvBuffer = NULL;
	int ret = 0;
	int uIndex = x*y;
	int vIndex = x*y*5/4;
	unsigned int i, j, k, l;
	unsigned char *out;

	yuvBuffer = (unsigned char*)malloc(sizeof(unsigned char)*x*y*3/2);
	if (!yuvBuffer) return 0;
	ret = standard_to_YUV420(inBuffer, size, x, y, yuvBuffer);
	if (!ret) {
		free(yuvBuffer);
		return 0;
	}

	out = outBuffer;
	// Y
	for (i=0; i<y; i+=T_Y)
		for (j=0; j<x; j+=T_X)
			for (k=0; k<T_Y; k++)
				for (l=0; l<T_X; l++)
					*out++ = yuvBuffer[(i+k)*x + j + l];
	// UV
	for (i=0; i<y/2; i+=T_Y) {
		for (j=0; j<x; j+=T_X) {
			for (k=0; k<T_Y; k++) {
				for (l=0; l<T_X/2; l++) {
					*out++ = yuvBuffer[uIndex + (i+k)*x + j + l*2];
					*out++ = yuvBuffer[uIndex + (i+k)*x + j + l*2 +1];
				}
			}
		}
	}

	free(yuvBuffer);
	return ret;
}


int output_RGB888(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path, int rawdata)
{
	return output_BMP(buffer, x, y, 24, RGB888, path, rawdata);
}

int output_ARGB8888(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path, int rawdata)
{
	return output_BMP(buffer, x, y, 32, ARGB8888, path, rawdata);
}

int output_ABGR8888(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path, int rawdata)
{
	return output_BMP(buffer, x, y, 32, ABGR8888, path, rawdata);
}

int output_XRGB8888(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path, int rawdata)
{
	return output_BMP(buffer, x, y, 32, XRGB8888, path, rawdata);
}

int output_XBGR8888(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path, int rawdata)
{
	return output_BMP(buffer, x, y, 32, XBGR8888, path, rawdata);
}

int output_ABGR1555(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path, int rawdata)
{
	return output_BMP(buffer, x, y, 16, ABGR1555, path, rawdata);
}

int output_RGBA5551(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path, int rawdata)
{
	return output_BMP(buffer, x, y, 16, RGBA5551, path, rawdata);
}

int output_ARGB4444(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path, int rawdata)
{
	return output_BMP(buffer, x, y, 16, ARGB4444, path, rawdata);
}

int output_RGB565(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path, int rawdata)
{
	return output_BMP(buffer, x, y, 16, RGB565, path, rawdata);
}

int output_BGR565(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path, int rawdata)
{
	return output_BMP(buffer, x, y, 16, BGR565, path, rawdata);
}

int output_YUV420(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path, int rawdata)
{
	FILE *f;

	_tfopen_s(&f, path, _T("wb"));
	if (f == NULL) return -1;
	fwrite(buffer, x*y*3/2, 1, f);
	fclose(f);

	return 0;
}

int output_TILEMODE(unsigned char *buffer, unsigned int x, unsigned int y, TCHAR *path, int rawdata)
{
	return output_YUV420(buffer, x, y, path, rawdata);
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
		case RGBA5551:
			/* RRRRRGGG GGBBBBBA */
			pal.alpha	= 0x1;
			pal.red		= 0xF800;
			pal.green	= 0x7C0;
			pal.blue	= 0x3E;
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
			   unsigned int bpp, Formats format, TCHAR *path, int rawdata)
{
	FILE *f;
	unsigned int i, remainder=0;

	_tfopen_s(&f, path, _T("wb"));
	if (f == NULL) return -1;
	if (!rawdata && output_BMP_Header(x, y, bpp, format, f)) return -1;

	if (x*bpp/8%4) remainder = 4-x*bpp/8%4;

	if (!rawdata) {
		for (i=y-1; (int)i>=0; i--) {
			fwrite(&buffer[i*(x*bpp/8+remainder)], x*bpp/8, 1, f);
			fwrite("\0", 1, remainder, f);
		}
	} else {
		for (i=0; i<y; i++) {
			fwrite(&buffer[i*(x*bpp/8+remainder)], x*bpp/8, 1, f);
			fwrite("\0", 1, remainder, f);
		}
	}
	fclose(f);

	return 0;
}