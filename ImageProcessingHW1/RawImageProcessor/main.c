#include <stdio.h>
#include "ImageProcessor.h"
#include "Problem1.h"

// Image files
#define RAWFILENAME	"rawImage.raw"
#define REFFILENAME	"lena_512x512.bmp"
#define BMPFILENAME	"bmpImage.bmp"
#define ROTFILENAME	"rotated_bmpImage.bmp"

int main(void) {
	
	BYTE rawArr[HEIGHT][WIDTH];	// Raw image pixel array
	BITMAPFILEHEADER bfh;		// Bitmap File Header
	BITMAPINFOHEADER bih;		// Bitmap Info Header
	RGBQUAD pal[256];			// Palette
	int errCode = 0;

	/*** 1. Generate a 512*512 RAW image. ***/
	errCode = genrateRAWofProblem1(RAWFILENAME, rawArr);
	if (errCode) {
		fprintf_s(stderr, "genrateRAWofProblem1() error [code: %d]\n", errCode);
		return errCode;
	}
	printf_s("RAW image is created. (%s)\n\n", RAWFILENAME);


	/*** 2. Generate a BMP image from the RAW image of the Problem 1. ***/
	errCode = readBMPHeader(REFFILENAME, &bfh, &bih, pal);	// Get BMP header
	if (errCode) {
		fprintf_s(stderr, "readBMPHeader() error [code: %d]\n", errCode);
		return errCode;
	}
	printf_s("Reading BMP header is completed. (%s)\n", REFFILENAME);
	printf_s("Image Size: (%3dx%3d)\n", bih.biWidth, bih.biHeight);
	printf_s("Pallete Type: %dbit Colors\n", bih.biBitCount);
	printf_s("Pixel Data Size: %d Bytes\n\n", bih.biSizeImage);
	
	errCode = convertRAWtoBMP(RAWFILENAME, BMPFILENAME, &bfh, &bih, pal);
	if (errCode) {
		fprintf_s(stderr, "convertRAWtoBMP() error [code: %d]\n", errCode);
		return errCode;
	}
	printf_s("BMP image is created. (%s)\n\n", BMPFILENAME);


	/*** 3. Rotate the BMP image of the Problem 2 clockwise. ***/
	errCode = rotateBMP(BMPFILENAME, ROTFILENAME);
	if (errCode) {
		fprintf_s(stderr, "rotateBMP() error [code: %d]\n", errCode);
		return errCode;
	}
	printf_s("Rotated BMP image is created. (%s)\n\n", ROTFILENAME);

	return 0;
}