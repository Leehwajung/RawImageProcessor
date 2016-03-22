#pragma once

// Brightness Type
typedef unsigned char brt;

// Two dimensional array of Brightness Type
// Form: [Height][Width]
typedef brt* brt2Darr;

/**
 * ### param ###
 *	rawFileName: output RAW file name
 *	rawArray: two dimensional array of brightness(brt)
 *	arrWidth: width of rawArray
 *	arrHeight: height of rawArray
 * 
 * ### return ###
 *	0: normal finish
 *	1: file open error
 */
int writeToRAW(const char* rawFileName, brt2Darr rawArray, unsigned int arrWidth, unsigned int arrHeight);

/**
 * ### param ###
 *	bmpFileName: input BMP file name
 *	bmpFileHeader: (OUT PARAM) bitmap file header 
 *	bmpInfoHeader: (OUT PARAM) bitmap info header
 *	bmpPalette: (OUT PARAM) bitmap palette (NULL is possible if bmpInfoHeader has more than 8-bit colors.)
 *
 * ### return ###
 *	0: normal finish
 *	1: file open error
 *	4: bmpFileHeader is NULL
 *	5: bmpInfoHeader is NULL
 *	6: bmpPalette is NULL, though bmpInfoHeader has less than 8-bit colors
 *	8: magic number error
 */
int getHeaderFromBMP(const char* bmpFileName, BITMAPFILEHEADER* bmpFileHeader, BITMAPINFOHEADER* bmpInfoHeader, RGBQUAD bmpPalette[256]);

/**
 * ### param ###
 *	rawFileName: input RAW file name
 *	bmpFileName: output BMP file name
 *	bmpFileHeader: bitmap file header 
 *	bmpInfoHeader: bitmap info header
 *	bmpPalette: bitmap palette (NULL is possible if bmpInfoHeader has more than 8-bit colors.)
 *
 * ### return ###
 *	0: normal finish
 *	1: RAW file open error
 *	2: BMP file open error
 *	4: bmpFileHeader is NULL
 *	5: bmpInfoHeader is NULL
 *	6: bmpPalette is NULL, though bmpInfoHeader has less than 8-bit colors
 *	8: magic number error
 */
int convertRAWtoBMP(const char* rawFileName, const char* bmpFileName, const BITMAPFILEHEADER* bmpFileHeader, const BITMAPINFOHEADER* bmpInfoHeader, const RGBQUAD bmpPalette[]);