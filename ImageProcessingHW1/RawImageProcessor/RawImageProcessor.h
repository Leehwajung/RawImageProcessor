#pragma once

// Brightness Type
typedef unsigned char brt;

// Two dimensional array of Brightness Type
// Form: [Height][Width]
typedef brt* brt2Darr;

/**
 * ### param ###
 *	fileName: output file name
 *	rawArray: two dimensional array of brightness(brt)
 *	arrWidth: width of rawArray
 *	arrHeight: height of rawArray
 * 
 * ### return ###
 *	0: normal finish
 *	1: file open error
 */
int writeToRawImage(const char* fileName, brt2Darr rawArray, unsigned int arrWidth, unsigned int arrHeight);