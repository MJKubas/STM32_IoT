#ifndef lock_closed_H_
#define lock_closed_H_

#include <stdint.h>

// struct packing, pragma for GCC !!!
#pragma pack(push, 1)



typedef struct lock_closed_tagBITMAPFILEHEADER {
  uint16_t   bfType;
  uint32_t   bfSize;
  uint16_t   bfReserved1;
  uint16_t   bfReserved2;
  uint32_t   bfOffBits;
} lock_closed_BITMAPFILEHEADER; // size is 14 bytes

typedef struct lock_closed_tagBITMAPINFOHEADER {
  uint32_t  biSize;
  uint32_t  biWidth;
  uint32_t  biHeight;
  uint16_t  biPlanes;
  uint16_t  biBitCount;
  uint32_t  biCompression;
  uint32_t  biSizeImage;
  uint32_t  biXPelsPerMeter;
  uint32_t  biYPelsPerMeter;
  uint32_t  biClrUsed;
  uint32_t  biClrImportant;
} lock_closed_BITMAPINFOHEADER; // size is 40 bytes

typedef struct lock_closed_tag_Struct {
  // offset 0, size 14
  lock_closed_BITMAPFILEHEADER fileHeader;
  // offset 14, size 40
  lock_closed_BITMAPINFOHEADER infoHeader;
  // offset 54, size 3600 words
  uint16_t data[3600];
} lock_closed_Struct;


lock_closed_Struct lock_closed = {
  {
    0x4d42u,
    sizeof(lock_closed_BITMAPINFOHEADER) + sizeof(lock_closed_BITMAPFILEHEADER) + (3600 * 2),
    0x0000u,
    0x0000u,
    sizeof(lock_closed_BITMAPINFOHEADER) + sizeof(lock_closed_BITMAPFILEHEADER)
  },
  {
    sizeof(lock_closed_BITMAPINFOHEADER),
    60,
    60,
    1u,
    16,
    0x00000003u,
    (3600 * 2),
    0x00000000ul,
    0x00000000ul,
    0x00000000ul,
    0x00000000ul
  },
  {
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0x0000, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0xd69a, 0x0000, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 
  0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208, 0x4208
  }
};



// struct packing, pragma for GCC !!!
#pragma pack (pop)



#endif /* lock_closed_H_ */
