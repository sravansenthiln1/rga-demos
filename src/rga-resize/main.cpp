#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "../../include/rga/RgaUtils.h"
#include "../../include/im2d/im2d.hpp"
#include "../../include/bmp/bmp.h"

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

        rga_buffer_t src_img, dst_img;
        rga_buffer_handle_t src_handle, dst_handle;

        int src_width = 1920;
        int src_height = 1080;
        int src_format = RK_FORMAT_RGB_888;

        int dst_width = 480;
        int dst_height = 270;
        int dst_format = RK_FORMAT_RGB_888;

        int src_buf_size = src_width * src_height * get_bpp_from_format(src_format);
        int dst_buf_size = dst_width * dst_height * get_bpp_from_format(dst_format);

    // flush RGA img buffers
        memset(&src_img, 0, sizeof(src_img));
        memset(&dst_img, 0, sizeof(dst_img));

    // allocate linux memory buffers for image 
        src_buf = (char*)malloc(src_buf_size);
        dst_buf = (char*)malloc(dst_buf_size);
        
    // read image data
        if (bmp_read(src_buf, "./input.bmp") != 0) {
                return -1;
        }

        src_handle = importbuffer_virtualaddr(src_buf, src_buf_size);
        dst_handle = importbuffer_virtualaddr(dst_buf, dst_buf_size);

        if (src_handle == 0 || dst_handle == 0) {
                printf("importbuffer failed!\n");
                goto release_buffer;
        }

        src_img = wrapbuffer_handle(src_handle, src_width, src_height, src_format);
        dst_img = wrapbuffer_handle(dst_handle, dst_width, dst_height, dst_format);
                
        start = get_cur_us();
        ret = imresize(src_img, dst_img, 0.25, 0.25);
        end = get_cur_us();

        printf("exec time: %ld us\n", end - start);

        if (ret != IM_STATUS_SUCCESS) {
            printf("error!, %s\n", imStrError((IM_STATUS)ret));
            goto release_buffer;
        }

        bmp_write(dst_buf, "./output.bmp", dst_width, dst_height);

    // release memory objects
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

