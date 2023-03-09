#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BUFFER_SIZE 80

void display_help() {
    printf("Usage: fcr [FILE]...\n");
    printf("Print FILE(s) content to standard output.\n");
}

int main(int argc, char** argv) {
    char buffer[BUFFER_SIZE];
    FILE* fd;

    int opt;
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
            case 'h':
                display_help();
                break;
            default:
                printf("Try \"fcr -h\" for more information.\n");
        }
    }

    int file_count = optind;
    if (argc > 1) {
        while(file_count < argc) {
            if (access(argv[file_count], F_OK) != 0) {
                printf("fcr: %s: %s\n", argv[file_count], strerror(errno));
                return 0;
            }

            fd = fopen(argv[file_count], "r");

            size_t lines_read;
            while((lines_read = fread(buffer, sizeof(char), BUFFER_SIZE, fd))) {
                fwrite(buffer, sizeof(char), lines_read, stdout);
            }

            fclose(fd);
            file_count++;
        }
    } else {
        display_help();
    }
}
