#pragma once
#include "ImageProcessor.h"

// Raw image size
#define HEIGHT	512
#define WIDTH	512

// Prototypes
/**
 * ### CAUTION ###
 *	Width size of rawArray must be greater than or equal to 512!
 *
 * ### return ###
 *	NORMFIN(0): normal finish
 *	FPNULL1(1): file open error
 */
int genrateRawImageOfProblem1(BYTE rawArray[HEIGHT][WIDTH], const char* rawFileName);

/**
 * ### CAUTION ###
 *	Size of brightnessArray must be greater than or equal to 512!
 */
void fillWithBrightnessOfProblem1(BYTE brightnessArray[]);