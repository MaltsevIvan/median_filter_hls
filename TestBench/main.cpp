
#include "BMPlib.h"
#include <iostream>
#include <cstring>

#define MAX_HEIGHT 800
//#define MAX_WIDTH 1920
#define MAX_WIDTH 800

typedef unsigned char pix_t;

static void getChannel(pix_t dest[MAX_HEIGHT][MAX_WIDTH], const unsigned char *src, unsigned char channel, unsigned int width, unsigned int height);
static void setChannel(unsigned char *dest, const pix_t src[MAX_HEIGHT][MAX_WIDTH], unsigned char channel, unsigned int width, unsigned int height);

void median_filter_image (pix_t in_pix[MAX_HEIGHT][MAX_WIDTH],
						  pix_t out_pix[MAX_HEIGHT][MAX_WIDTH],
						  short int height,
						  short int width);

int main(int argc, char *argv[]) {
	if (argc < 3) return 1;

	std::cout << argv[1] << "\n" << argv[2] << std::endl;

	BMPlib::BMP bmpIn;
	bmpIn.Read(argv[1]);
	bmpIn.ConvertTo(BMPlib::BMP::COLOR_MODE::RGB);

	const short int width = bmpIn.GetWidth();
	const short int height = bmpIn.GetHeight();
	const unsigned int channelLength = width * height;

	BMPlib::BMP bmpOut(bmpIn.GetWidth(), bmpIn.GetHeight(), BMPlib::BMP::COLOR_MODE::RGB);

	unsigned int length = bmpIn.GetWidth() * bmpIn.GetHeight() * 3;
	const unsigned char *bufferIn = bmpIn.GetPixelBuffer();

	std::cout << bmpIn.GetWidth() << "x" << bmpIn.GetHeight() << std::endl;

	std::cout << (int)bufferIn[bmpIn.GetWidth() * 3] << ", " << (int)bufferIn[bmpIn.GetWidth() * 3 + 1] << ", " << (int)bufferIn[bmpIn.GetWidth() * 3 + 2] << std::endl;

	static pix_t redIn[MAX_HEIGHT][MAX_WIDTH], greenIn[MAX_HEIGHT][MAX_WIDTH], blueIn[MAX_HEIGHT][MAX_WIDTH];
	static pix_t redOut[MAX_HEIGHT][MAX_WIDTH], greenOut[MAX_HEIGHT][MAX_WIDTH], blueOut[MAX_HEIGHT][MAX_WIDTH];

	getChannel(redIn, bufferIn, 0, width, height);
	getChannel(greenIn, bufferIn, 1, width, height);
	getChannel(blueIn, bufferIn, 2, width, height);

	median_filter_image(redIn, redOut, height, width);
	median_filter_image(greenIn, greenOut, height, width);
	median_filter_image(blueIn, blueOut, height, width);

	unsigned char *bufferOut = bmpOut.GetPixelBuffer();

	setChannel(bufferOut, redOut, 0, width, height);
	setChannel(bufferOut, greenOut, 1, width, height);
	setChannel(bufferOut, blueOut, 2, width, height);

	bmpOut.Write(argv[2]);

	return 0;
}

void getChannel(pix_t dest[MAX_HEIGHT][MAX_WIDTH], const unsigned char *src, unsigned char channel, unsigned int width, unsigned int height) {
	for (unsigned int j = 0; j < height; j++) {
		for (unsigned int i = 0; i < width; i++) {
			dest[i][j] = src[(width * j + i) * 3 + channel];
		}
	}
}

void setChannel(unsigned char *dest, const pix_t src[MAX_HEIGHT][MAX_WIDTH], unsigned char channel, unsigned int width, unsigned int height) {
	for (unsigned int j = 0; j < height; j++) {
		for (unsigned int i = 0; i < width; i++) {
			dest[(width * j + i) * 3 + channel] = src[i][j];
		}
	}
}
