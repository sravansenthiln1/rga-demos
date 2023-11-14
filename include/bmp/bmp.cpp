#include "bmp.h"
#include <stdio.h>

int bmp_read(void *buf, const char *path) {
    int size;

    FILE *file = fopen(path, "rb");
    if (!file) {
        fprintf(stderr, "Could not open %s\n", path);
        return -1;
    }

    // read bmp header
    bmp_header bmpHeader;
    fread(&bmpHeader, sizeof(bmp_header), 1, file);

    // check file validity (bmp, 24 bpp)
    if (bmpHeader.type != 0x4D42 || bmpHeader.bpp != 24) {
        fprintf(stderr, "Invalid BMP file format\n");
        fclose(file);
        return -1;
    }

    // calculate the size of image data
    size = bmpHeader.width * bmpHeader.height * 3;  // 3 bytes per pixel for 24bpp

    // read image data
    fread(buf, size, 1, file);

    fclose(file);

    return 0;
}

int bmp_write(void *buf, const char *path, int w, int h) {
    int size;

    FILE *file = fopen(path, "wb+");
    if (!file) {
        fprintf(stderr, "Could not open %s\n", path);
        return -1;
    }

    // create a bitmap header
    bmp_header bmpHeader = {
        .type = 0x4D42,
        .size = sizeof(bmp_header) + w * h * 3,
        .reserved1 = 0,
        .reserved2 = 0,
        .offset = sizeof(bmp_header),
        .header_size = 40,
        .width = w,
        .height = h,
        .planes = 1,
        .bpp = 24,
        .compression = 0,
        .image_size = w * h * 3,
        .x_pixels_per_m = 0,
        .y_pixels_per_m = 0,
        .colors_used = 0,
        .colors_important = 0
    };

    // write bmp header
    fwrite(&bmpHeader, sizeof(bmp_header), 1, file);

    // write image data
    size = w * h * 3;  // 3 bytes per pixel for 24bpp
    fwrite(buf, size, 1, file);
    
    fclose(file);

    return 0;
}
