#include <stdio.h>
#include "../../include/im2d/im2d.h"

int main(void) {
        printf("RGA Info:\n");
        printf("%s", querystring(RGA_ALL));

        return(0);
}
