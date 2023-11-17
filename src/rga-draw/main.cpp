#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "../../libs/rga/include/RgaUtils.h"
#include "../../libs/im2d/include/im2d.hpp"
#include "../../libs/bmp/include/bmp.h"
#include "../../libs/dma/include/dma_alloc.h"

int main(void) {
    /* Print API revision version */
    printf("%s", querystring(RGA_API_REVISION_VERSION));

    /* Initialize variables */
    int ret = 0;
    int64_t start, end;

    /* Destination buffer pointers and DMA file descriptor */
    char* dst_buf;
    int dst_dma_fd;

    /* Destination RGA buffer and handle */
    rga_buffer_t dst_img;
    rga_buffer_handle_t dst_handle;

    /* Destination image dimensions and format */
    int dst_width = 1920;
    int dst_height = 1080;
    int dst_format = RK_FORMAT_RGBA_8888;

    /* Number of rectangles and array of rectangle structures */
    int num_rectangles = 3;
    im_rect rectangles[num_rectangles];

    rectangles[0].x = 256;
    rectangles[0].y = 256;
    rectangles[0].width = 512;
    rectangles[0].height = 512;

    rectangles[1].x = 256;
    rectangles[1].y = 256;
    rectangles[1].width = 256;
    rectangles[1].height = 256;

    rectangles[2].x = 256;
    rectangles[2].y = 256;
    rectangles[2].width = 128;
    rectangles[2].height = 128;

    /* Calculate buffer size */
    int dst_buf_size = dst_width * dst_height * get_bpp_from_format(dst_format);

    /* Flush RGA image buffer */
    memset(&dst_img, 0, sizeof(dst_img));

    /* Allocate Linux memory buffer for image using DMA */
    ret = dma_buf_alloc(DMA_HEAP_DMA32_PATCH, dst_buf_size, &dst_dma_fd, (void **)&dst_buf);
    if (ret < 0) {
        printf("alloc dst dma_heap buffer failed!\n");
        dma_buf_free(dst_buf_size, &dst_dma_fd, dst_buf);
        return -1;
    }

    /* Import memory buffer into RGA handle */
    dst_handle = importbuffer_fd(dst_dma_fd, dst_buf_size);

    /* Check if buffer import was successful */
    if (dst_handle == 0) {
        printf("importbuffer failed!\n");
        goto release_buffer;
    }

    /* Wrap RGA handle with image information */
    dst_img = wrapbuffer_handle(dst_handle, dst_width, dst_height, dst_format);

    /* Perform image drawing with rectangles */
    start = get_cur_us();
    ret = imrectangleArray(dst_img, rectangles, num_rectangles, 0xffffffff, 2);
    end = get_cur_us();

    /* Print execution time */
    printf("exec time: %ld us\n", end - start);

    /* Check for drawing errors */
    if (ret != IM_STATUS_SUCCESS) {
        printf("error!, %s\n", imStrError((IM_STATUS)ret));
        goto release_buffer;
    }

    /* Write the drawn image to output file */
    bmp_write(dst_buf, "./output.bmp", dst_width, dst_height);

    /* Release memory objects */
    release_buffer:
    if (dst_handle)
        releasebuffer_handle(dst_handle);

    if (dst_buf)
        dma_buf_free(dst_buf_size, &dst_dma_fd, dst_buf);

    return(0);
}
