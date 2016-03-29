#include "ImageProcessor.h"

#include <stdlib.h>	// for malloc()

int writeRAW(const char* rawFileName, const BYTE pixelData[], const unsigned int pixelDataSize) {

	FILE *ofp;
	unsigned int i;

	// Open output file
	fopen_s(&ofp, rawFileName, "wb");

	if (ofp == NULL) {
		return FPNULL1;
	}

	// Write RAW image file
	for (i = 0; i < pixelDataSize; i++) {
		fputc(pixelData[i], ofp);
	}
	
	fclose(ofp);

	return NORMFIN;
}

int readBMPHeader(const char* bmpFileName, 
		LPBITMAPFILEHEADER bmpFileHeader, LPBITMAPINFOHEADER bmpInfoHeader, 
		RGBQUAD bmpPalette[]) {

	FILE *ifp;
	int errCode = 0;

	// Open input file
	fopen_s(&ifp, bmpFileName, "rb");

	if (ifp == NULL) {
		return FPNULL1;
	}

	// Read BMP Header
	errCode = getBMPHeader(ifp, bmpFileHeader, bmpInfoHeader, bmpPalette);

	fclose(ifp);

	return errCode;
}

int writeBMP(const char* bmpFileName, 
	const LPBITMAPFILEHEADER bmpFileHeader, const LPBITMAPINFOHEADER bmpInfoHeader, 
	const RGBQUAD bmpPalette[], const BYTE pixelData[]) {

	FILE *ofp;
	WORD pixelBufSize;
	int errCode = 0;

	// Open output file
	fopen_s(&ofp, bmpFileName, "wb");
	if (ofp == NULL) {
		return FPNULL1;
	}

	// Write BMP image file
	pixelBufSize = getPixelBufSize(bmpInfoHeader->biBitCount);
	errCode = putBMPHeader(ofp, bmpFileHeader, bmpInfoHeader, bmpPalette);
	if (!errCode) {
		fwrite(pixelData, pixelBufSize, bmpInfoHeader->biSizeImage, ofp);
	}
	fclose(ofp);

	return errCode;
}

int convertRAWtoBMP(const char* rawFileName,  const char* bmpFileName, 
		const LPBITMAPFILEHEADER bmpFileHeader, const LPBITMAPINFOHEADER bmpInfoHeader, 
		const RGBQUAD bmpPalette[]) {
	
	BYTE *pixelData;
	FILE *ifp;
	WORD pixelBufSize;
	int errCode = 0, i;

	// Open input files
	fopen_s(&ifp, rawFileName, "rb");
	if (ifp == NULL) {
		return FPNULL1;
	}

	// Read RAW image data
	pixelData = malloc(bmpInfoHeader->biSizeImage);
	pixelBufSize = getPixelBufSize(bmpInfoHeader->biBitCount);
	
	for (i = bmpInfoHeader->biHeight - 1; i >= 0; i--) {	// Up-down reverse
		fread_s(&pixelData[i * bmpInfoHeader->biWidth * pixelBufSize],
			bmpInfoHeader->biWidth * pixelBufSize, pixelBufSize, bmpInfoHeader->biWidth, ifp);
	}
	fclose(ifp);

	// Write BMP image file
	errCode = writeBMP(bmpFileName, bmpFileHeader, bmpInfoHeader, bmpPalette, pixelData);
	if (errCode == FPNULL1) {
		errCode = FPNULL2;
	}

	// Deallocate memory
	free(pixelData);

	return errCode;
}

int rotateBMP(const char* srcFileName, const char* dstFileName) {

	BITMAPFILEHEADER bfh;	// Bitmap File Header
	BITMAPINFOHEADER bih;	// Bitmap Info Header
	RGBQUAD pal[256];		// Palette
	BYTE *pixelData;		// Pixel Data

	FILE *ifp;
	WORD pixelBufSize;
	LONG tmpWidth;
	int errCode = 0, i, j;

	// Open input file
	fopen_s(&ifp, srcFileName, "rb");
	if (ifp == NULL) {
		return FPNULL1;
	}

	// Read source BMP header
	errCode = getBMPHeader(ifp, &bfh, &bih, pal);
	if (errCode) {
		fclose(ifp);
		return errCode;
	}
	if (bih.biBitCount < 8) {	// Is pixel size greater than or equal to 8-bits?
		fclose(ifp);
		return NOTSPRT;	// Not support 1-bit and 4-bits image
	}

	// Rotate BMP image clockwise
	pixelData = malloc(bih.biSizeImage);
	pixelBufSize = getPixelBufSize(bih.biBitCount);

	tmpWidth = bih.biWidth;
	bih.biWidth = bih.biHeight;
	bih.biHeight = tmpWidth;

	for (i = 0; i < bih.biWidth; i++) {
		for (j = bih.biHeight - 1; j >= 0; j--) {
			fread_s(&pixelData[(i + j * bih.biWidth) * pixelBufSize],
				pixelBufSize, pixelBufSize, 1, ifp);
		}
	}
	fclose(ifp);

	// Write destination BMP image File
	errCode = writeBMP(dstFileName, &bfh, &bih, pal, pixelData);
	if (errCode == FPNULL1) {
		errCode = FPNULL2;
	}

	// Deallocate memory
	free(pixelData);

	return errCode;
}

int getBMPHeader(FILE* bmpFilePointer, 
		LPBITMAPFILEHEADER bmpFileHeader, LPBITMAPINFOHEADER bmpInfoHeader, 
		RGBQUAD bmpPalette[]) {

	// Check header arguments
	if (!bmpFileHeader) {
		return BFHNULL;
	}
	if (!bmpInfoHeader) {
		return BIHNULL;
	}

	// Read header from BMP image file
	fread_s(bmpFileHeader, sizeof(BITMAPFILEHEADER), 
		sizeof(BITMAPFILEHEADER), 1, bmpFilePointer);	// Read file header
	if (bmpFileHeader->bfType != MAGICNUM) {	// Check magic number
		return MGNBERR;
	}

	fread_s(bmpInfoHeader, sizeof(BITMAPINFOHEADER), 
		sizeof(BITMAPINFOHEADER), 1, bmpFilePointer);	// Read image header 

	if (bmpInfoHeader->biBitCount <= 8) {		// Has palette?
		if (bmpPalette) {
			fread_s(bmpPalette, sizeof(RGBQUAD) * 256, 
				sizeof(RGBQUAD), 256, bmpFilePointer);	// Read palette
		}
		else {
			return PALNULL;
		}
	}

	return NORMFIN;
}

int putBMPHeader(FILE* bmpFilePointer,
		const LPBITMAPFILEHEADER bmpFileHeader, const LPBITMAPINFOHEADER bmpInfoHeader, 
		const RGBQUAD bmpPalette[]) {

	// Check header arguments
	if (!bmpFileHeader) {
		return BFHNULL;
	}
	if (!bmpInfoHeader) {
		return BIHNULL;
	}

	// write header to BMP image file
	if (bmpFileHeader->bfType != MAGICNUM) {	// Check magic number
		return MGNBERR;
	}
	fwrite(bmpFileHeader, sizeof(BYTE), 
		sizeof(BITMAPFILEHEADER), bmpFilePointer); // Write file header

	fwrite(bmpInfoHeader, sizeof(BYTE), 
		sizeof(BITMAPINFOHEADER), bmpFilePointer); // Write image header

	if (bmpInfoHeader->biBitCount <= 8) {		// Has palette?
		if (bmpPalette) {
			fwrite(bmpPalette, sizeof(RGBQUAD), 
				256, bmpFilePointer);				// Write palette
		}
		else {
			return PALNULL;
		}
	}

	return NORMFIN;
}

WORD getPixelBufSize(WORD bitCount) {

	bitCount = bitCount / 8;

	return bitCount >= 1 ? bitCount : 1;
}