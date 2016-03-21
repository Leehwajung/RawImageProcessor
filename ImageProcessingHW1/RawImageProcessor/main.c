#include <stdio.h>
#include "RawImageProcessor.h"

// Raw image size
#define HEIGHT	512
#define WIDTH	512

// Raw image file name
#define OUTPUTFILENAME	"rawImage.raw"

int genrateRawImageOfQ1(brt2Darr rawArr);
void fillWithBrightnessOfQ1(brt brightnessArray[]);

int main(void) {
	
	// 1. Generate the 512¡¿512 raw image.
	brt rawArr[HEIGHT][WIDTH];

	if (genrateRawImageOfQ1((brt2Darr)rawArr)) {
		fprintf_s(stderr, "File open error!\n");
		return 1;
	}

	printf_s("Raw image is created.\n");


	return 0;
}

/**
 * ### CAUTION ###
 *	Width size of rawArr must be greater than or equal to 512!
 * 
 * ### return ###
 *	0: normal finish
 *	1: file open error
 */
int genrateRawImageOfQ1(brt2Darr rawArr) {

	brt brtArr[WIDTH];
	int i, j;

	fillWithBrightnessOfQ1(brtArr);

	for (i = 0; i < WIDTH; i++) {		// width
		for (j = 0; j < HEIGHT; j++) {	// height
			rawArr[j * WIDTH + i] = brtArr[i];
		}
	}

	return writeToRawImage(OUTPUTFILENAME, rawArr, WIDTH, HEIGHT);
}

/**
 * ### CAUTION ###
 *	Width size of rawArr must be greater than or equal to 512!
 */
void fillWithBrightnessOfQ1(brt brightnessArray[]) {

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