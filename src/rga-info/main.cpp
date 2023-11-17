#include <stdio.h>

#include "../../libs/im2d/include/im2d.h"

int main(void) {
    /* Print RGA information */
    printf("RGA Info:\n");
    printf("%s", querystring(RGA_ALL));

    return 0;
}
