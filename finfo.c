/************************************************
* Name: Marshall Molinski
* Assignment Name: Lab 9 - System Calls
* Section: CPE2600 111
************************************************/
// finfo.c

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>

void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("File type: Regular file\n");
    } else if (S_ISDIR(mode)) {
        printf("File type: Directory\n");
    } else if (S_ISCHR(mode)) {
        printf("File type: Character device\n");
    } else if (S_ISBLK(mode)) {
        printf("File type: Block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("File type: FIFO (named pipe)\n");
    } else if (S_ISLNK(mode)) {
        printf("File type: Symbolic link\n");
    } else if (S_ISSOCK(mode)) {
        printf("File type: Socket\n");
    } else {
        printf("File type: Unknown\n");
    }
}

void print_permissions(mode_t mode) {
    printf("Permissions: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
    struct stat file_info;

    // Get file information
    if (stat(filename, &file_info) == -1) {
        perror("Error getting file information");
        return 1;
    }

    //Print file type
    print_file_type(file_info.st_mode);

    // Print file permissions
    print_permissions(file_info.st_mode);

    // Print file owner
    printf("Owner (UID): %d\n", file_info.st_uid);

    // Print file size in bytes
    printf("File size: %ld bytes\n", file_info.st_size);

    // Print last modification time
    char time_buffer[26];
    struct tm *time_info = localtime(&file_info.st_mtime);
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", time_info);
    printf("Last modified: %s\n", time_buffer);
    return 0;
}
