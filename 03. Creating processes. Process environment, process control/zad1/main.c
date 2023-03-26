#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        return 1;
    }
    int i;
    const int n = (int) strtol(argv[1], NULL, 10);
    if (n <= 0) {
        printf("Invalid number of processes\n");
        return 1;
    }

    // Create n processes
    for (i = 0; i < n; i++) {
        const pid_t child_pid = fork();
        if (child_pid == 0) {
            printf("Process id: %d, Parent id: %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        }
        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }
    // Wait for all children to terminate
    for (i = 0; i < n; i++) {
        if (wait(NULL) == -1) {
            perror("wait");
        }
    }
    printf("Ran %d processes\n", n);
    return 0;
}



