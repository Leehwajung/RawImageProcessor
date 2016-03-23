#include "Problem1.h"

#include "ImageProcessor.h"

int genrateRawImageOfProblem1(BYTE rawArray[HEIGHT][WIDTH], const char* rawFileName) {

	BYTE brtArr[WIDTH];
	int i, j;

	fillWithBrightnessOfProblem1(brtArr);

	for (i = 0; i < WIDTH; i++) {		// width
		for (j = 0; j < HEIGHT; j++) {	// height
			rawArray[j][i] = brtArr[i];
		}
	}

	return writeToRAW(rawFileName, (BYTE*)rawArray, WIDTH * HEIGHT);
}

void fillWithBrightnessOfProblem1(BYTE brightnessArray[]) {

	int i = 0;

	// 0 <= n <= 100
	for (i; i <= 100; i++) {
		brightnessArray[i] = 120;
	}

	// 100 < n < 200
	for (i; i < 200; i++) {
		brightnessArray[i] = (BYTE)(0.15 * i + 105);
	}

	// 200 <= n < 280
	for (i; i < 280; i++) {
		brightnessArray[i] = (BYTE)(1.125 * i - 90);
	}

	// 280 <= n < 300
	for (i; i < 300; i++) {
		brightnessArray[i] = (BYTE)(0.75 * i + 15);
	}

	// 300 <= n < 512
	for (i; i < 512; i++) {
		brightnessArray[i] = 240;
	}
}