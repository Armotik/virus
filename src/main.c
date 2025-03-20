#include <stdio.h>
#include "find_exec.h"
#include "open_image.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    display_image(argv[1]);
    find_executable_files(".");

    return 0;
}