#ifndef BMP_H
#define BMP_H

#include <stdint.h>

// bitmap file header structure
#pragma pack(2)
typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_m;
    int32_t y_pixels_per_m;
    uint32_t colors_used;
    uint32_t colors_important;
} bmp_header;
#pragma pack()

int bmp_read(void *buf, const char *path);

int bmp_write(void *buf, const char *path, int w, int h);

#endif // BMP_H
