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

    /* Source and destination buffer pointers */
    char* src_buf;
    char* dst_buf;

    /* File descriptors for DMA buffers */
    int src_dma_fd;
    int dst_dma_fd;

    /* Source and destination RGA buffers and handles */
    rga_buffer_t src_img, dst_img;
    rga_buffer_handle_t src_handle, dst_handle;

    /* Image dimensions and formats */
    int src_width = 1920;
    int src_height = 1080;
    int src_format = RK_FORMAT_RGBA_8888;

    int dst_width = 1920;
    int dst_height = 1080;
    int dst_format = RK_FORMAT_RGBA_8888;

    /* Calculate buffer sizes */
    int src_buf_size = src_width * src_height * get_bpp_from_format(src_format);
    int dst_buf_size = dst_width * dst_height * get_bpp_from_format(dst_format);

    /* Flush RGA image buffers */
    memset(&src_img, 0, sizeof(src_img));
    memset(&dst_img, 0, sizeof(dst_img));

    /* Allocate Linux memory buffers for images using DMA */
    ret = dma_buf_alloc(DMA_HEAP_UNCACHE_PATH, src_buf_size, &src_dma_fd, (void **)&src_buf);
    if (ret < 0) {
        printf("alloc src dma_heap buffer failed!\n");
        dma_buf_free(src_buf_size, &src_dma_fd, src_buf);
        return -1;
    }

    ret = dma_buf_alloc(DMA_HEAP_UNCACHE_PATH, dst_buf_size, &dst_dma_fd, (void **)&dst_buf);
    if (ret < 0) {
        printf("alloc dst dma_heap buffer failed!\n");
        dma_buf_free(dst_buf_size, &dst_dma_fd, dst_buf);
        return -1;
    }

    /* Read image data */
    if (bmp_read(src_buf, "./input_rgba.bmp") != 0) {
        return -1;
    }

    /* DMA sync: Transfer data from device to CPU for both source and destination buffers */
    dma_sync_device_to_cpu(src_dma_fd);
    dma_sync_device_to_cpu(dst_dma_fd);

    /* Import memory buffers into RGA handles */
    src_handle = importbuffer_fd(src_dma_fd, src_buf_size);
    dst_handle = importbuffer_fd(dst_dma_fd, dst_buf_size);

    /* Check if buffer import was successful */
    if (src_handle == 0 || dst_handle == 0) {
        printf("importbuffer failed!\n");
        goto release_buffer;
    }

    /* Wrap RGA handles with image information */
    src_img = wrapbuffer_handle(src_handle, src_width, src_height, src_format);
    dst_img = wrapbuffer_handle(dst_handle, dst_width, dst_height, dst_format);

    /* Perform image copy */
    start = get_cur_us();
    ret = imcopy(src_img, dst_img);
    end = get_cur_us();

    /* Print execution time */
    printf("exec time: %ld us\n", end - start);

    /* Check for copying errors */
    if (ret != IM_STATUS_SUCCESS) {
        printf("error!, %s\n", imStrError((IM_STATUS)ret));
        goto release_buffer;
    }

    /* DMA sync: Transfer data from device to CPU for both source and destination buffers */
    dma_sync_device_to_cpu(src_dma_fd);
    dma_sync_device_to_cpu(dst_dma_fd);

    /* Write the copied image to output file */
    bmp_write(dst_buf, "./output.bmp", dst_width, dst_height);

    /* Release memory objects and DMA buffers */
    release_buffer:
    if (src_handle)
        releasebuffer_handle(src_handle);
    if (dst_handle)
        releasebuffer_handle(dst_handle);

    dma_buf_free(src_buf_size, &src_dma_fd, src_buf);
    dma_buf_free(dst_buf_size, &dst_dma_fd, dst_buf);

    return(0);
}
