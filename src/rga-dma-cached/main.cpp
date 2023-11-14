#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "../../include/rga/RgaUtils.h"
#include "../../include/im2d/im2d.hpp"
#include "../../include/bmp/bmp.h"
#include "../../include/dma/dma_alloc.h"

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

int main(void) {
        printf("%s", querystring(RGA_API_REVISION_VERSION));

        int ret = 0;
        int64_t start, end;

        char* src_buf;
        char* dst_buf;

        int src_dma_fd;
        int dst_dma_fd;

        rga_buffer_t src_img, dst_img;
        rga_buffer_handle_t src_handle, dst_handle;

        int src_width = 1920;
        int src_height = 1080;
        int src_format = RK_FORMAT_RGB_888;

        int dst_width = 1920;
        int dst_height = 1080;
        int dst_format = RK_FORMAT_RGB_888;

        int src_buf_size = src_width * src_height * get_bpp_from_format(src_format);
        int dst_buf_size = dst_width * dst_height * get_bpp_from_format(dst_format);

    // flush RGA img buffers
        memset(&src_img, 0, sizeof(src_img));
        memset(&dst_img, 0, sizeof(dst_img));

    // allocate linux memory buffers for image 
        ret = dma_buf_alloc(DMA_HEAP_UNCACHE_PATH, src_buf_size, &src_dma_fd, (void **)&src_buf);
        if (ret < 0) {
            printf("alloc src dma_heap buffer failed!\n");
            return -1;
        }

        ret = dma_buf_alloc(DMA_HEAP_UNCACHE_PATH, dst_buf_size, &dst_dma_fd, (void **)&dst_buf);
        if (ret < 0) {
            printf("alloc dst dma_heap buffer failed!\n");
            dma_buf_free(src_buf_size, &src_dma_fd, src_buf);
            return -1;
        }
        
    // read image data
        if (bmp_read(src_buf, "./input.bmp") != 0) {
                return -1;
        }

        src_handle = importbuffer_fd(src_dma_fd, src_buf_size);
        dst_handle = importbuffer_fd(dst_dma_fd, dst_buf_size);

        if (src_handle == 0 || dst_handle == 0) {
                printf("importbuffer failed!\n");
                goto release_buffer;
        }

        src_img = wrapbuffer_handle(src_handle, src_width, src_height, src_format);
        dst_img = wrapbuffer_handle(dst_handle, dst_width, dst_height, dst_format);
                
        start = get_cur_us();
        ret = imcopy(src_img, dst_img);
        end = get_cur_us();

        printf("exec time: %ld us\n", end - start);

        if (ret != IM_STATUS_SUCCESS) {
            printf("error!, %s\n", imStrError((IM_STATUS)ret));
            goto release_buffer;
        }

    // sync the dma buf to the cpu
        dma_sync_device_to_cpu(src_dma_fd);
        dma_sync_device_to_cpu(dst_dma_fd);

        bmp_write(dst_buf, "./output.bmp", dst_width, dst_height);

    // release memory objects
        release_buffer:
        if (src_handle)
                releasebuffer_handle(src_handle);
        if (dst_handle)
                releasebuffer_handle(dst_handle);

        dma_buf_free(src_buf_size, &src_dma_fd, src_buf);
        dma_buf_free(dst_buf_size, &dst_dma_fd, dst_buf);

        return(0);
}
