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
#define PALNULL		6	// Palette(RGBQUAD*) arg is error
#define MGNBERR		8	// magic number error (NOT 0x4D42)
#define NOTSPRT		16	// not support 1-bit or 4-bits image

// Prototypes
/**
 * Write a RAW image from the byte array.
 * 
 * ### param ###
 *	rawFileName: output file name (RAW)
 *	pixelData: array of brightness pixel data (BYTE)
 *	pixelDataSize: size of pixelData (width * height)
 * 
 * ### return ###
 *	NORMFIN(0): normal finish
 *	FPNULL1(1): file open error
 */
int writeRAW(const char* rawFileName, const BYTE pixelData[], const unsigned int pixelDataSize);

/**
 * Read a BMP header from the BMP image.
 * 
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
 *	MGNBERR(8): magic number error (NOT 0x4D42)
 */
int readBMPHeader(const char* bmpFileName, LPBITMAPFILEHEADER bmpFileHeader, LPBITMAPINFOHEADER bmpInfoHeader, RGBQUAD bmpPalette[256]);

/**
 * Write a BMP image from BMP header and byte array.
 *
 * ### param ###
 *	bmpFileName: output file name (BMP)
 *	bmpFileHeader: bitmap file header 
 *	bmpInfoHeader: bitmap info header
 *	bmpPalette: bitmap palette (NULL is possible if bmpInfoHeader has more than 8-bit colors.)
 *	pixelData: array of pixel data (BYTE)
 * 
 * ### return ###
 *	NORMFIN(0): normal finish
 *	FPNULL1(1): file open error
 *	BFHNULL(4): bmpFileHeader is NULL
 *	BIHNULL(5): bmpInfoHeader is NULL
 *	PALNULL(6): bmpPalette is NULL, though bmpInfoHeader has less than 8-bit colors
 *	MGNBERR(8): magic number error (NOT 0x4D42)
 */
int writeBMP(const char* bmpFileName, const LPBITMAPFILEHEADER bmpFileHeader, const LPBITMAPINFOHEADER bmpInfoHeader, const RGBQUAD bmpPalette[], const BYTE pixelData[]);

/**
 * Convert the RAW image to a BMP image.
 *
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
 *	MGNBERR(8): magic number error (NOT 0x4D42)
 */
int convertRAWtoBMP(const char* rawFileName, const char* bmpFileName, const LPBITMAPFILEHEADER bmpFileHeader, const LPBITMAPINFOHEADER bmpInfoHeader, const RGBQUAD bmpPalette[]);

/**
 * Rotate the BMP image and write a new BMP image.
 * 
 * ### param ###
 *	srcFileName: source file name (BMP)
 *	dstFileName: destination file name (BMP)
 * 
 * ### return ###
 *	NORMFIN(0): normal finish
 *	FPNULL1(1): source file open error
 *	FPNULL2(2): destination file open error
 *	MGNBERR(8): not BMP image file (magic number error, NOT 0x4D42)
 *	NOTSPRT(16): not support 1-bit or 4-bits image
 */
int rotateBMP(const char* srcFileName, const char* dstFileName);

/**
 * Get a BMP header from the input file stream of BMP image.
 * 
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
 *	MGNBERR(8): magic number error (NOT 0x4D42)
 */
int getBMPHeader(FILE* bmpFilePointer, LPBITMAPFILEHEADER bmpFileHeader, LPBITMAPINFOHEADER bmpInfoHeader, RGBQUAD bmpPalette[]);

/**
 * Put the BMP header to the output file stream of BMP image.
 * 
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
 *	MGNBERR(8): magic number error (NOT 0x4D42)
 */
int putBMPHeader(FILE* bmpFilePointer, const LPBITMAPFILEHEADER bmpFileHeader, const LPBITMAPINFOHEADER bmpInfoHeader, const RGBQUAD bmpPalette[]);

/**
 * Get pixel buffer size (bits) from pixel byte size for file read or write.
 * 
 * ### param ###
 *	bitCount: pixel byte size
 * 
 * ### return ###
 *	pixel buffer size (bits)
 */
WORD getPixelBufSize(WORD bitCount);