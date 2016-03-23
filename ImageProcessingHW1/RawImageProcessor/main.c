#include <stdio.h>
#include "RawImageProcessor.h"
#include "Problem1.h"

// Image files
#define RAWFILENAME	"rawImage.raw"
#define REFFILENAME	"lena_512x512.bmp"
#define BMPFILENAME	"bmpImage.bmp"

int main(void) {
	
	int errCode = 0;

	/*** 1. Generate the 512¡¿512 RAW image. ***/
	brt rawArr[HEIGHT][WIDTH];

	errCode = genrateRawImageOfProblem1((brt2Darr)rawArr, RAWFILENAME);
	if (errCode) {
		fprintf_s(stderr, "genrateRawImageOfProblem1() error [code: %d]\n", errCode);
		return errCode;
	}

	printf_s("RAW image is created. (%s)\n\n", RAWFILENAME);


	/*** 2. Generate a BMP image from RAW image of Problem 1. ***/
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	RGBQUAD pal[256];

	errCode = getHeaderFromBMP(REFFILENAME, &bfh, &bih, pal);	// Get BMP header
	if (errCode) {
		fprintf_s(stderr, "getHeaderFromBmp() error [code: %d]\n", errCode);
		return errCode;
	}
	printf_s("Reading BMP header is completed. (%s)\n", REFFILENAME);
	printf_s("Image Size: (%3dx%3d)\n", bih.biWidth, bih.biHeight);
	printf_s("Pallete Type: %dbit Colors\n", bih.biBitCount);
	printf_s("Pixel Data Size: %d Bytes\n\n", bih.biSizeImage);
	
	errCode = convertRAWtoBMP(RAWFILENAME, BMPFILENAME, &bfh, &bih, pal);
	if (errCode) {
		fprintf_s(stderr, "convertRawToBmp() error [code: %d]\n", errCode);
		return errCode;
	}

	printf_s("BMP image is created. (%s)\n\n", BMPFILENAME);

	return 0;
}