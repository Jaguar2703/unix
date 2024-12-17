#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void file_lock(int fd) {
    struct flock fl;

    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;

    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }

    printf("File locked successfully!\n");
}

void file_unlock(int fd) {
    struct flock fl;

    fl.l_type = F_UNLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;

    if (fcntl(fd, F_SETLK, &fl) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }

    printf("File unlocked successfully!\n");
}

int main() {
    int fd;
    char *filename = "testfile.txt";

    if ((fd = open(filename, O_RDWR | O_CREAT, 0666)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (write(fd, "Hello, world!\n", 14) != 14) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    file_lock(fd);

    if (write(fd, "Locked file content\n", 20) == -1) {
        perror("write");
        printf("Error: Cannot write to the locked file.\n");
    }

    file_unlock(fd);

    if (write(fd, "Unlocked file content\n", 22) != 22) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    close(fd);

    return 0;
}
