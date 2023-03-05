#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void display_help() {
    printf("Usage: fcr [FILE]...\n");
    printf("Print FILE(s) content to standard output.\n");
    printf("\n  -n            number all output lines\n");
}

int main(int argc, char** argv) {
    bool number = false;
    FILE* fd;

    int opt;
    while ((opt = getopt(argc, argv, "nh")) != -1) {
        switch(opt) {
            case 'n':
                number = true;
                break;
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

            int line_number = 0;
            while(!feof(fd)) {
                int ch = fgetc(fd);

                putchar(ch);
                if (number && ch == '\n') {
                    printf("%d  ", line_number++);
                }
            }

            fclose(fd);
            file_count++;
        }
    } else {
        display_help();
    }
}
