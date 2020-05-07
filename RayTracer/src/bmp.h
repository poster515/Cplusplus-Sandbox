/**
 * BMP-related data types based on Microsoft's own.
 */

#include <stdint.h>

/**
 * Common Data Types
 *
 * The data types in this section are essentially aliases for C/C++
 * primitive data types.
 *
 * Adapted from https://msdn.microsoft.com/en-us/library/cc230309.aspx.
 * See http://en.wikipedia.org/wiki/Stdint.h for more on stdint.h.
 */
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

/**
 * BITMAPFILEHEADER
 *
 * The BITMAPFILEHEADER structure contains information about the type, size,
 * and layout of a file that contains a DIB [device-independent bitmap].
 *
 * Adapted from https://msdn.microsoft.com/en-us/library/dd183374(v=vs.85).aspx.
 */
typedef struct
{
    WORD bfType;    //0x00 The file type; must be BM.
    DWORD bfSize;   //0x02 The size, in bytes, of the bitmap file.
    WORD bfReserved1; //0x06
    WORD bfReserved2; //0x08
    DWORD bfOffBits;    //0x0A The offset, in bytes, from the beginning of the BITMAPFILEHEADER structure to the bitmap bits.
} __attribute__((__packed__))
BITMAPFILEHEADER;

/**
 * BITMAPINFOHEADER
 *
 * The BITMAPINFOHEADER structure contains information about the
 * dimensions and color format of a DIB [device-independent bitmap].
 *
 * Adapted from https://msdn.microsoft.com/en-us/library/dd183376(v=vs.85).aspx.
 */
typedef struct
{
    DWORD biSize; //0x0E The number of bytes required by the structure.
    LONG biWidth; //0x12 The width of the bitmap, in pixels.
    LONG biHeight; //0x16 The height of the bitmap, in pixels.
    WORD biPlanes; //0x1A
    WORD biBitCount; //0x1C The number of bits-per-pixel.
    DWORD biCompression; //0x1E
    DWORD biSizeImage;  //0x22 The size, in bytes, of the image.
    LONG biXPelsPerMeter; //0x26
    LONG biYPelsPerMeter; //0x2A
    DWORD biClrUsed;      //0x2E
    DWORD biClrImportant; //0x32
} __attribute__((__packed__))
BITMAPINFOHEADER;

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

