#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void create_zombie_process() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        printf("Parent process created a zombie process (PID: %d)\n", pid);
    } else {
        printf("Zombie process created (PID: %d)\n", getpid());
        exit(EXIT_SUCCESS);
    }
}

void prevent_zombie_processes() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        printf("Parent process created a child process (PID: %d)\n", pid);
        sleep(2);
    } else {
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            printf("First child process (PID: %d) exited\n", getpid());
            exit(EXIT_SUCCESS);
        } else {
            printf("Grandchild process (PID: %d)\n", getpid());
            sleep(5);
            printf("Grandchild process completed\n");
            exit(EXIT_SUCCESS);
        }
    }
}

void create_orphan_process() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        printf("Parent process (PID: %d)\n", getpid());
        sleep(2);
    } else {
        printf("Orphan process created (PID: %d)\n", getpid());
        sleep(5);
        printf("Orphan process completed\n");
        exit(EXIT_SUCCESS);
    }
}

void parent_child_scenario() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        printf("Parent process (PID: %d)\n", getpid());
        wait(NULL);
    } else {
        printf("Child process (PID: %d)\n", getpid());
        exit(EXIT_SUCCESS);
    }
}

int main() {
    printf("1. Creating a zombie process:\n");
    create_zombie_process();

    printf("\n2. Preventing zombie processes:\n");
    prevent_zombie_processes();

    printf("\n3. Creating an orphan process:\n");
    create_orphan_process();

    printf("\n4. Parent-child scenario:\n");
    parent_child_scenario();

    return 0;
}
