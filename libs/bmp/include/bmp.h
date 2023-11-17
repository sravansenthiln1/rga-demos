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

/**
 * @brief Reads an RGBA bitmap from a file into a buffer.
 *
 * This function reads an RGBA bitmap from the specified file path and stores the pixel data in the provided buffer.
 *
 * @param buf Pointer to the buffer where the bitmap data will be stored.
 * @param path The file path of the RGBA bitmap to be read.
 * @return 0 on success, -1 on failure.
 */
int bmp_read(void *buf, const char *path);

/**
 * @brief Writes an RGBA bitmap to a file from a buffer.
 *
 * This function writes the RGBA bitmap data from the provided buffer to the specified file path.
 *
 * @param buf Pointer to the buffer containing the RGBA bitmap data.
 * @param path The file path where the RGBA bitmap will be written.
 * @param w Width of the bitmap.
 * @param h Height of the bitmap.
 * @return 0 on success, -1 on failure.
 */
int bmp_write(void *buf, const char *path, int w, int h);

/**
 * @brief Gets the current time in milliseconds.
 *
 * This function returns the current time in milliseconds.
 *
 * @return Current time in milliseconds.
 */
int64_t get_cur_ms();

/**
 * @brief Gets the current time in microseconds.
 *
 * This function returns the current time in microseconds.
 *
 * @return Current time in microseconds.
 */
int64_t get_cur_us();

#endif // BMP_H
