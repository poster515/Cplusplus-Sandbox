/*
 * rgb.h
 *
 *  Created on: May 9, 2020
 *      Author: Jpost
 */

#ifndef RGB_H_
#define RGB_H_

#include <stdint.h>
typedef uint8_t  BYTE;
/**
 * RGBTRIPLE
 *
 * This structure describes a color consisting of relative intensities of
 * red, green, and blue.
 *
 * Adapted from https://msdn.microsoft.com/en-us/library/dd162939(v=vs.85).aspx.
 */
typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;

#endif /* RGB_H_ */
