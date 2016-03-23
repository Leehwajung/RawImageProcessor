#pragma once
#include "RawImageProcessor.h"

// Raw image size
#define HEIGHT	512
#define WIDTH	512

// Prototypes
/**
 * ### CAUTION ###
 *	Width size of rawArray must be greater than or equal to 512!
 *
 * ### return ###
 *	0: normal finish
 *	1: file open error
 */
int genrateRawImageOfProblem1(brt2Darr rawArray, const char* rawFileName);

/**
 * ### CAUTION ###
 *	Size of brightnessArray must be greater than or equal to 512!
 */
void fillWithBrightnessOfProblem1(brt brightnessArray[]);