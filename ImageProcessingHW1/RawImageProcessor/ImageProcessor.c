#include "ImageProcessor.h"

#include <stdlib.h>

int writeToRAW(const char* rawFileName, BYTE rawArray[], unsigned int arrSize) {

	FILE *ofp;
	unsigned int i;

	// Open output file
	fopen_s(&ofp, rawFileName, "wb");

	if (ofp == NULL) {
		return FPNULL1;
	}

	// Write raw image
	for (i = 0; i < arrSize; i++) {
		fputc(rawArray[i], ofp);
	}
	
	fclose(ofp);

	return NORMFIN;
}

int getBMPHeader(const char* bmpFileName,
	LPBITMAPFILEHEADER bmpFileHeader, LPBITMAPINFOHEADER bmpInfoHeader, RGBQUAD bmpPalette[]) {

	FILE *ifp;
	int errCode = 0;

	// Open input file
	fopen_s(&ifp, bmpFileName, "rb");

	if (ifp == NULL) {
		return FPNULL1;
	}

	// Read BMP Header
	errCode = readBMPHeader(ifp, bmpFileHeader, bmpInfoHeader, bmpPalette);

	fclose(ifp);

	return errCode;
}

int convertRAWtoBMP(const char* rawFileName,  const char* bmpFileName,
		const LPBITMAPFILEHEADER bmpFileHeader, const LPBITMAPINFOHEADER bmpInfoHeader, const RGBQUAD bmpPalette[]) {
	
	BYTE *pixelData;
	FILE *ifp, *ofp;
	int pixelBufSize;
	int errCode = 0, i;

	// Open input/output files
	fopen_s(&ifp, rawFileName, "rb");
	fopen_s(&ofp, bmpFileName, "wb");

	if (ifp == NULL) {
		return FPNULL1;
	}
	if (ofp == NULL) {
		return FPNULL2;
	}

	// Read raw image data
	pixelBufSize = bmpInfoHeader->biBitCount / 8;
	pixelBufSize = pixelBufSize >= 1 ? pixelBufSize : 1;
	pixelData = malloc(pixelBufSize * bmpInfoHeader->biSizeImage);
	for (i = bmpInfoHeader->biHeight - 1; i >= 0; i--) {	// Up-down reverse
		fread_s(&pixelData[i * pixelBufSize * bmpInfoHeader->biWidth], pixelBufSize * bmpInfoHeader->biWidth, pixelBufSize, bmpInfoHeader->biWidth, ifp);
	}

	fclose(ifp);

	// Write bmp image
	errCode = writeBMPHeader(ofp, bmpFileHeader, bmpInfoHeader, bmpPalette);
	if (!errCode) {
		fwrite(pixelData, pixelBufSize, bmpInfoHeader->biSizeImage, ofp);
	}
	fclose(ofp);

	// Deallocate memory
	free(pixelData);

	return errCode;
}

int ratateBMP(const char* srcFileName, const char* dstFileName) {

	BITMAPFILEHEADER bfh;	// Bitmap File Header
	BITMAPINFOHEADER bih;	// Bitmap Info Header
	RGBQUAD pal[256];		// Palette
	BYTE *pixelData;

	FILE *ifp, *ofp;
	LONG tmpWidth;
	int pixelBufSize;
	int errCode = 0, i, j;

	// Open input/output files
	fopen_s(&ifp, srcFileName, "rb");
	fopen_s(&ofp, dstFileName, "wb");

	if (ifp == NULL) {
		return FPNULL1;
	}
	if (ofp == NULL) {
		return FPNULL2;
	}

	// Read source BMP header
	errCode = readBMPHeader(ifp, &bfh, &bih, pal);
	if (errCode) {
		fclose(ifp);
		return errCode;
	}

	// Rotate BMP image clockwise
	pixelBufSize = bih.biBitCount / 8;
	pixelBufSize = pixelBufSize >= 1 ? pixelBufSize : 1;	// For 1-bit or 4-bits image
	pixelData = malloc(pixelBufSize * bih.biSizeImage);

	tmpWidth = bih.biWidth;
	bih.biWidth = bih.biHeight;
	bih.biHeight = tmpWidth;

	if (bih.biBitCount >= 8) {	// Is pixel size greater than or equal to 8-bit?
		for (j = bih.biWidth - 1; j >= 0; j--) {
			for (i = bih.biHeight - 1; i >= 0; i--) {
				fread_s(&pixelData[(i * bih.biWidth + j) * pixelBufSize], pixelBufSize, pixelBufSize, 1, ifp);
			}
		}
	}
	else {
		// TODO: Support 1-bit and 4-bits image
	}
	fclose(ifp);
	
	// Write destination bmp image
	errCode = writeBMPHeader(ofp, &bfh, &bih, pal);	// Set BMP Header
	if (!errCode) {
		fwrite(pixelData, pixelBufSize, bih.biSizeImage, ofp);
	}
	fclose(ofp);

	// Deallocate memory
	free(pixelData);

	return errCode;
}

int readBMPHeader(FILE* bmpFilePointer,
	LPBITMAPFILEHEADER bmpFileHeader, LPBITMAPINFOHEADER bmpInfoHeader, RGBQUAD bmpPalette[]) {

	// Check header arguments
	if (!bmpFileHeader) {
		return BFHNULL;
	}
	if (!bmpInfoHeader) {
		return BIHNULL;
	}

	// Read header from bmp file
	fread_s(bmpFileHeader, sizeof(BITMAPFILEHEADER), sizeof(BITMAPFILEHEADER), 1, bmpFilePointer); // Read file header
	if (bmpFileHeader->bfType != MAGICNUM) {	// Check magic number
		return MGNNULL;
	}

	fread_s(bmpInfoHeader, sizeof(BITMAPINFOHEADER), sizeof(BITMAPINFOHEADER), 1, bmpFilePointer); // Read image header 

	if (bmpInfoHeader->biBitCount <= 8) {	// Has palette?
		if (bmpPalette) {
			fread_s(bmpPalette, sizeof(RGBQUAD) * 256, sizeof(RGBQUAD), 256, bmpFilePointer);		// Read palette
		}
		else {
			return PALNULL;
		}
	}

	return NORMFIN;
}

int writeBMPHeader(FILE* bmpFilePointer,
	const LPBITMAPFILEHEADER bmpFileHeader, const LPBITMAPINFOHEADER bmpInfoHeader, const RGBQUAD bmpPalette[]) {

	// Check header arguments
	if (!bmpFileHeader) {
		return BFHNULL;
	}
	if (!bmpInfoHeader) {
		return BIHNULL;
	}

	// write header to bmp file
	if (bmpFileHeader->bfType != MAGICNUM) {	// Check magic number
		return MGNNULL;
	}
	fwrite(bmpFileHeader, sizeof(BYTE), sizeof(BITMAPFILEHEADER), bmpFilePointer); // Write file header

	fwrite(bmpInfoHeader, sizeof(BYTE), sizeof(BITMAPINFOHEADER), bmpFilePointer); // Write image header

	if (bmpInfoHeader->biBitCount <= 8) {	// Has palette?
		if (bmpPalette) {
			fwrite(bmpPalette, sizeof(RGBQUAD), 256, bmpFilePointer);				// Write palette
		}
		else {
			return PALNULL;
		}
	}

	return NORMFIN;
}