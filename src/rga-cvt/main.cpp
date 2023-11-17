#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "../../libs/rga/include/RgaUtils.h"
#include "../../libs/im2d/include/im2d.hpp"
#include "../../libs/bmp/include/bmp.h"

/* Function to write NV12 data to a file */
int nv12_write(const char *buf, const char *path, int width, int height) {
    int size;

    FILE *file = fopen(path, "wb");
    if (!file) {
        fprintf(stderr, "Could not open %s\n", path);
        return -1;
    }

    size = width * height * 3 / 2;
    fwrite(buf, size, 1, file);

    fclose(file);

    return 0;
}

/* Main function */
int main(void) {
    /* Print API revision version */
    printf("%s", querystring(RGA_API_REVISION_VERSION));

    /* Initialize variables */
    int ret = 0;
    int64_t start, end;

    /* Source and destination buffer pointers */
    char* src_buf;
    char* dst_buf;

    /* Source and destination RGA buffers and handles */
    rga_buffer_t src_img, dst_img;
    rga_buffer_handle_t src_handle, dst_handle;

    /* Image dimensions and formats */
    int src_width = 1920;
    int src_height = 1080;
    int src_format = RK_FORMAT_RGBA_8888;

    int dst_width = 1920;
    int dst_height = 1080;
    int dst_format = RK_FORMAT_YCrCb_420_SP;

    /* Calculate buffer sizes */
    int src_buf_size = src_width * src_height * get_bpp_from_format(src_format);
    int dst_buf_size = dst_width * dst_height * get_bpp_from_format(dst_format);

    /* Flush RGA image buffers */
    memset(&src_img, 0, sizeof(src_img));
    memset(&dst_img, 0, sizeof(dst_img));

    /* Allocate Linux memory buffers for images */
    src_buf = (char*)malloc(src_buf_size);
    dst_buf = (char*)malloc(dst_buf_size);

    /* Read image data */
    if (bmp_read(src_buf, "./input_rgba.bmp") != 0) {
        return -1;
    }

    /* Import memory buffers into RGA handles */
    src_handle = importbuffer_virtualaddr(src_buf, src_buf_size);
    dst_handle = importbuffer_virtualaddr(dst_buf, dst_buf_size);

    /* Check if buffer import was successful */
    if (src_handle == 0 || dst_handle == 0) {
        printf("importbuffer failed!\n");
        goto release_buffer;
    }

    /* Wrap RGA handles with image information */
    src_img = wrapbuffer_handle(src_handle, src_width, src_height, src_format);
    dst_img = wrapbuffer_handle(dst_handle, dst_width, dst_height, dst_format);

    /* Perform color conversion */
    start = get_cur_us();
    ret = imcvtcolor(src_img, dst_img, src_format, dst_format, IM_RGB_TO_YUV_BT709_LIMIT);
    end = get_cur_us();

    /* Print execution time */
    printf("exec time: %ld us\n", end - start);

    /* Check for color conversion errors */
    if (ret != IM_STATUS_SUCCESS) {
        printf("error!, %s\n", imStrError((IM_STATUS)ret));
        goto release_buffer;
    }

    /* Write the converted image to output file */
    nv12_write(dst_buf, "./output.nv12", dst_width, dst_height);

    /* Release memory objects */
    release_buffer:
    if (src_handle)
        releasebuffer_handle(src_handle);
    if (dst_handle)
        releasebuffer_handle(dst_handle);

    if (src_buf)
        free(src_buf);
    if (dst_buf)
        free(dst_buf);

    return(0);
}
