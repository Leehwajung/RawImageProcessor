#pragma once
#include "ImageProcessor.h"

// Raw image size
#define HEIGHT	512
#define WIDTH	512

// Prototypes
/**
 * Generate a 512*512 RAW image, each row of which is a smooth ramp r(n) as shown in the figure of Problem 1.
 * 
 * ### CAUTION ###
 *	WIDTH size of rawArray must be greater than or equal to 512!
 * 
 * ### param ###
 *	rawFileName: output file name (RAW)
 *	rawArray: (OUT PARAM) brightness pixel data of the Problem 1 (BYTE)
 * 
 * ### return ###
 *	NORMFIN(0): normal finish
 *	FPNULL1(1): file open error
 */
int genrateRAWofProblem1(const char* rawFileName, BYTE rawArray[HEIGHT][WIDTH]);

/**
 * Get brightness values[r(n)] as shown in the figure of Problem 1.
 * 
 * ### CAUTION ###
 *	Size of brightnessArray must be greater than or equal to 512!
 * 
 * ### param ###
 *	brightnessArray: (OUT PARAM) brightness values of the Problem 1 (BYTE)
 */
void getBrightnessOfProblem1(BYTE brightnessArray[]);