#include "RawImageProcessor.h"

#include <stdio.h>
#include <stdlib.h>

int writeToRAW(const char* rawFileName, brt2Darr rawArray, unsigned int arrWidth, unsigned int arrHeight) {

	FILE *ofp;
	unsigned int i, j;

	// Open output file
	fopen_s(&ofp, rawFileName, "wb");

	if (ofp == NULL) {
		return 1;
	}

	// Write raw image
	for (i = 0; i < arrHeight; i++) {		// Height
		for (j = 0; j < arrWidth; j++) {	// Width
			fputc(rawArray[i * arrWidth + j], ofp);
		}
	}
	
	fclose(ofp);

	return 0;
}

int getHeaderFromBMP(const char* bmpFileName,
	BITMAPFILEHEADER* bmpFileHeader, BITMAPINFOHEADER* bmpInfoHeader, RGBQUAD bmpPalette[]) {

	FILE *ifp;

	// Check header arguments
	if (!bmpFileHeader) {
		return 4;
	}
	if (!bmpInfoHeader) {
		return 5;
	}

	// Open input file
	fopen_s(&ifp, bmpFileName, "rb");

	if (ifp == NULL) {
		return 1;
	}

	// Read header from bmp file
	fread_s(bmpFileHeader, sizeof(BITMAPFILEHEADER), sizeof(BITMAPFILEHEADER), 1, ifp); // Read file header
	if (bmpFileHeader->bfType != 0x4D42) {	// Check magic number
		return 8;
	}

	fread_s(bmpInfoHeader, sizeof(BITMAPINFOHEADER), sizeof(BITMAPINFOHEADER), 1, ifp); // Read image header 

	if (bmpInfoHeader->biBitCount <= 8) {	// Has palette?
		if (bmpPalette) {
			fread_s(bmpPalette, sizeof(RGBQUAD) * 256, sizeof(RGBQUAD), 256, ifp);		// Read palette
		}
		else {
			return 6;
		}
	}

	fclose(ifp);

	return 0;
}

int convertRAWtoBMP(const char* rawFileName,  const char* bmpFileName,
		const BITMAPFILEHEADER* bmpFileHeader, const BITMAPINFOHEADER* bmpInfoHeader, const RGBQUAD bmpPalette[]) {

	FILE *ifp, *ofp;
	int i;

	// Check header arguments
	if (!bmpFileHeader) {
		return 4;
	}
	if (!bmpInfoHeader) {
		return 5;
	}

	// Open input/output files
	fopen_s(&ifp, rawFileName, "rb");
	fopen_s(&ofp, bmpFileName, "wb");

	if (ifp == NULL) {
		return 1;
	}
	if (ofp == NULL) {
		return 2;
	}

	// Read raw image data
	brt *pixelData = (brt*) malloc(sizeof(brt) * bmpInfoHeader->biSizeImage);
	for (i = bmpInfoHeader->biHeight - 1; i >= 0; i--) {	// Up-down reverse
		fread_s(&pixelData[i * bmpInfoHeader->biWidth], sizeof(brt) * bmpInfoHeader->biWidth, sizeof(brt), bmpInfoHeader->biWidth, ifp);
	}
	fclose(ifp);

	// Write bmp image
	fwrite(bmpFileHeader, sizeof(BYTE), sizeof(BITMAPFILEHEADER), ofp);
	fwrite(bmpInfoHeader, sizeof(BYTE), sizeof(BITMAPINFOHEADER), ofp);
	if (bmpInfoHeader->biBitCount <= 8) {	// Has palette?
		if (bmpPalette) {
			fwrite(bmpPalette, sizeof(RGBQUAD), 256, ofp);
		}
		else {
			return 6;
		}
	}
	fwrite(pixelData, sizeof(brt), bmpInfoHeader->biSizeImage, ofp);
	fclose(ofp);

	// Deallocate memory
	free(pixelData);

	return 0;
}