#pragma once
#include <stdio.h>
#include <Windows.h>

// BMP Magic Number
#define MAGICNUM	0x4D42

// Error Code
#define NORMFIN		0	// normal finish
#define FPNULL1		1	// first file arg open error
#define FPNULL2		2	// second file arg open error
#define BFHNULL		4	// LPBITMAPFILEHEADER arg is NULL
#define BIHNULL		5	// LPBITMAPINFOHEADER arg is NULL
#define PALNULL		6	// Palette(RGBQUAD*) error
#define MGNNULL		8	// magic number error (NOT 0x4D42)

// Prototypes
/**
 * ### param ###
 *	rawFileName: output file name (RAW)
 *	rawArray: two dimensional array of brightness(BYTE)
 *	arrSize: size of rawArray (width * height)
 * 
 * ### return ###
 *	NORMFIN(0): normal finish
 *	FPNULL1(1): file open error
 */
int writeToRAW(const char* rawFileName, BYTE rawArray[], unsigned int arrSize);

/**
 * ### param ###
 *	bmpFileName: input file name (BMP)
 *	bmpFileHeader: (OUT PARAM) bitmap file header 
 *	bmpInfoHeader: (OUT PARAM) bitmap info header
 *	bmpPalette: (OUT PARAM) bitmap palette (NULL is possible if bmpInfoHeader has more than 8-bit colors.)
 *
 * ### return ###
 *	NORMFIN(0): normal finish
 *	FPNULL1(1): file open error
 *	BFHNULL(4): bmpFileHeader is NULL
 *	BIHNULL(5): bmpInfoHeader is NULL
 *	PALNULL(6): bmpPalette is NULL, though bmpInfoHeader has less than 8-bit colors
 *	MGNNULL(8): magic number error (NOT 0x4D42)
 */
int getBMPHeader(const char* bmpFileName, LPBITMAPFILEHEADER bmpFileHeader, LPBITMAPINFOHEADER bmpInfoHeader, RGBQUAD bmpPalette[256]);

/**
 * ### param ###
 *	rawFileName: input file name (RAW)
 *	bmpFileName: output file name (BMP)
 *	bmpFileHeader: bitmap file header 
 *	bmpInfoHeader: bitmap info header
 *	bmpPalette: bitmap palette (NULL is possible if bmpInfoHeader has more than 8-bit colors.)
 *
 * ### return ###
 *	NORMFIN(0): normal finish
 *	FPNULL1(1): RAW file open error
 *	FPNULL2(2): BMP file open error
 *	BFHNULL(4): bmpFileHeader is NULL
 *	BIHNULL(5): bmpInfoHeader is NULL
 *	PALNULL(6): bmpPalette is NULL, though bmpInfoHeader has less than 8-bit colors
 *	MGNNULL(8): magic number error (NOT 0x4D42)
 */
int convertRAWtoBMP(const char* rawFileName, const char* bmpFileName, const LPBITMAPFILEHEADER bmpFileHeader, const LPBITMAPINFOHEADER bmpInfoHeader, const RGBQUAD bmpPalette[]);

/**
 * ### param ###
 *	srcFileName: source file name (BMP)
 *	dstFileName: destination file name (BMP)
 *
 * ### return ###
 *	NORMFIN(0): normal finish
 *	FPNULL1(1): source file open error
 *	FPNULL2(2): destination file open error
 *	MGNNULL(8): not bmp file (magic number error, NOT 0x4D42)
 */
int ratateBMP(const char* srcFileName, const char* dstFileName);

/**
 * ### param ###
 *	bmpFilePointer: read-able file pointer of BMP file
 *	bmpFileHeader: (OUT PARAM) bitmap file header 
 *	bmpInfoHeader: (OUT PARAM) bitmap info header
 *	bmpPalette: (OUT PARAM) bitmap palette (NULL is possible if bmpInfoHeader has more than 8-bit colors.)
 *
 * ### return ###
 *	NORMFIN(0): normal finish
 *	BFHNULL(4): bmpFileHeader is NULL
 *	BIHNULL(5): bmpInfoHeader is NULL
 *	PALNULL(6): bmpPalette is NULL, though bmpInfoHeader has less than 8-bit colors
 *	MGNNULL(8): magic number error (NOT 0x4D42)
 */
int readBMPHeader(FILE* bmpFilePointer, LPBITMAPFILEHEADER bmpFileHeader, LPBITMAPINFOHEADER bmpInfoHeader, RGBQUAD bmpPalette[]);

/**
 * ### param ###
 *	bmpFilePointer: writable file pointer of BMP file
 *	bmpFileHeader: bitmap file header 
 *	bmpInfoHeader: bitmap info header
 *	bmpPalette: bitmap palette (NULL is possible if bmpInfoHeader has more than 8-bit colors.)
 *
 * ### return ###
 *	NORMFIN(0): normal finish
 *	BFHNULL(4): bmpFileHeader is NULL
 *	BIHNULL(5): bmpInfoHeader is NULL
 *	PALNULL(6): bmpPalette is NULL, though bmpInfoHeader has less than 8-bit colors
 *	MGNNULL(8): magic number error (NOT 0x4D42)
 */
int writeBMPHeader(FILE* bmpFilePointer, const LPBITMAPFILEHEADER bmpFileHeader, const LPBITMAPINFOHEADER bmpInfoHeader, const RGBQUAD bmpPalette[]);