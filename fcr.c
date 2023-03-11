#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BUFFER_SIZE 80

void print_help() {
    printf("Usage: fcr [FILE]...\n");
    printf("Print FILE(s) content to standard output.\n");
}

void print_content(char* file_name) {
    FILE* fd = fopen(file_name, "r");
    char buffer[BUFFER_SIZE];
    
    if (!fd) {
        printf("fcr: %s: %s\n", file_name, strerror(errno));
        return;
    }

    size_t lines_read;
    while((lines_read = fread(buffer, sizeof(char), BUFFER_SIZE, fd))) {
        fwrite(buffer, sizeof(char), lines_read, stdout);
    }

    fclose(fd);
}

int main(int argc, char** argv) {
    int opt;
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
            case 'h':
                print_help();
                break;
            default:
                printf("Try \"fcr -h\" for more information.\n");
        }
    }

    int file_index = optind;
    if (argc > 1) {
        while (file_index < argc) {
            print_content(argv[file_index]);
            file_index++;
        }
    } else {
        print_help();
    }
}
