#include "include/bmp.h"
#include <stdio.h>
#include <sys/time.h>

int64_t get_cur_us() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

int64_t get_cur_ms() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

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

    // check file validity (bmp, 32 bpp)
    if (bmpHeader.type != 0x4D42 || bmpHeader.bpp != 32) {
        fprintf(stderr, "Invalid BMP file format\n");
        fclose(file);
        return -1;
    }

    // calculate the size of image data
    size = bmpHeader.width * bmpHeader.height * 4;  // 4 bytes per pixel for 32bpp

    // read image data
    int64_t start = get_cur_us();
    fread(buf, size, 1, file);
    int64_t end = get_cur_us();

    fclose(file);

    // calculate read speed
    double speed = ((double)size / (double)(end - start));

    printf("read %d bytes at %.f MB/s\n", size, speed);

    return(0);
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
        .size = sizeof(bmp_header) + w * h * 4,
        .reserved1 = 0,
        .reserved2 = 0,
        .offset = sizeof(bmp_header),
        .header_size = 40,
        .width = w,
        .height = h,
        .planes = 1,
        .bpp = 32,
        .compression = 0,
        .image_size = w * h * 4,
        .x_pixels_per_m = 0,
        .y_pixels_per_m = 0,
        .colors_used = 0,
        .colors_important = 0
    };

    // write bmp header
    fwrite(&bmpHeader, sizeof(bmp_header), 1, file);

    // write image data
    size = w * h * 4;  // 4 bytes per pixel for 32bpp

    int64_t start = get_cur_us();
    fwrite(buf, size, 1, file);

    int64_t end = get_cur_us();

    fclose(file);

    // calculate read speed
    double speed = ((double)size / (double)(end - start));

    printf("wrote %d bytes at %.2f MB/s\n", size, speed);

    return(0);
}
