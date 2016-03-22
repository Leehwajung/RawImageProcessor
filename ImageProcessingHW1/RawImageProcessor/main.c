#include <stdio.h>
#include <Windows.h>
#include "RawImageProcessor.h"

// Raw image size
#define HEIGHT	512
#define WIDTH	512

// Image file names
#define RAWFILENAME	"rawImage.raw"
#define REFFILENAME	"lena_512x512.bmp"
#define BMPFILENAME	"bmpImage.bmp"

// Prototypes
int genrateRawImageOfProblem1(brt2Darr rawArray);
void fillWithBrightnessOfProblem1(brt brightnessArray[]);

int main(void) {
	
	int errCode = 0;

	/*** 1. Generate the 512¡¿512 RAW image. ***/
	brt rawArr[HEIGHT][WIDTH];

	errCode = genrateRawImageOfProblem1((brt2Darr)rawArr);
	if (errCode) {
		fprintf_s(stderr, "genrateRawImageOfProblem1() error [code: %d]\n", errCode);
		return errCode;
	}

	printf_s("RAW image is created. (%s)\n\n", RAWFILENAME);


	/*** 2. Generate a BMP image from RAW image of Problem 1. ***/
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hInfo;
	RGBQUAD hRGB[256];

	errCode = getHeaderFromBMP(REFFILENAME, &hf, &hInfo, hRGB);	// Get BMP header
	if (errCode) {
		fprintf_s(stderr, "getHeaderFromBmp() error [code: %d]\n", errCode);
		return errCode;
	}
	printf_s("Reading BMP header is completed. (%s)\n", REFFILENAME);
	printf_s("Image Size: (%3dx%3d)\n", hInfo.biWidth, hInfo.biHeight);
	printf_s("Pallete Type: %dbit Colors\n", hInfo.biBitCount);
	printf_s("Pixel Data Size: %d Bytes\n\n", hInfo.biSizeImage);
	
	errCode = convertRAWtoBMP(RAWFILENAME, BMPFILENAME, &hf, &hInfo, hRGB);
	if (errCode) {
		fprintf_s(stderr, "convertRawToBmp() error [code: %d]\n", errCode);
		return errCode;
	}

	printf_s("BMP image is created. (%s)\n\n", BMPFILENAME);

	return 0;
}

/**
 * ### CAUTION ###
 *	Width size of rawArray must be greater than or equal to 512!
 * 
 * ### return ###
 *	0: normal finish
 *	1: file open error
 */
int genrateRawImageOfProblem1(brt2Darr rawArray) {

	brt brtArr[WIDTH];
	int i, j;

	fillWithBrightnessOfProblem1(brtArr);

	for (i = 0; i < WIDTH; i++) {		// width
		for (j = 0; j < HEIGHT; j++) {	// height
			rawArray[j * WIDTH + i] = brtArr[i];
		}
	}

	return writeToRAW(RAWFILENAME, rawArray, WIDTH, HEIGHT);
}

/**
 * ### CAUTION ###
 *	Size of brightnessArray must be greater than or equal to 512!
 */
void fillWithBrightnessOfProblem1(brt brightnessArray[]) {

	int i = 0;

	// 0 <= n <= 100
	for (i; i <= 100; i++) {
		brightnessArray[i] = 120;
	}

	// 100 < n < 200
	for (i; i < 200; i++) {
		brightnessArray[i] = (brt) (0.15 * i + 105);
	}

	// 200 <= n < 280
	for (i; i < 280; i++) {
		brightnessArray[i] = (brt) (1.125 * i - 90);
	}

	// 280 <= n < 300
	for (i; i < 300; i++) {
		brightnessArray[i] = (brt) (0.75 * i + 15);
	}

	// 300 <= n < 512
	for (i; i < 512; i++) {
		brightnessArray[i] = 240;
	}
}