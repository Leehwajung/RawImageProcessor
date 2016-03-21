#include <stdio.h>
#include "RawImageProcessor.h"

int writeToRawImage(const char* fileName, brt2Darr rawArray, unsigned int arrWidth, unsigned int arrHeight) {

	FILE *fp;
	int i, j;

	fopen_s(&fp, fileName, "w");

	if (fp == NULL) {
		return 1;
	}

	for (i = 0; i < arrHeight; i++) {		// arrHeight
		for (j = 0; j < arrWidth; j++) {	// arrWidth
			fputc(rawArray[i * arrWidth + j], fp);
		}
	}
	
	fclose(fp);

	return 0;
}