#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>

#define PATTER_SIZE 255
#define PATH_MAX 4096

void check_path(const char *res, const char *path) {
    if (res == NULL && path[0] != '/') {
        printf("Error when resolving path\n");
        exit(EXIT_FAILURE);
    }
}

void check_pattern(const char *child_path, char *buffer, const char *pattern, const size_t pattern_size) {
    FILE *file = fopen(child_path, "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    const size_t size = fread(buffer, sizeof(char), pattern_size, file);

    buffer[size] = 0;

    if (strcmp(buffer, pattern) == 0) {
        printf("path: %s pid: %d\n", child_path, getpid());
        fflush(NULL);
    }
    fclose(file);
}

void search_dir(const char *exe_path, const char *curr_path, const char *pattern) {
    DIR *dir = opendir(curr_path);

    if (dir == NULL) {
        perror("open_dir");
        exit(EXIT_FAILURE);
    }
    struct dirent *ent;
    char child_path[PATH_MAX];
    while ((ent = readdir(dir))) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;

        strcpy(child_path, curr_path);
        strcat(child_path, "/");
        strcat(child_path, ent->d_name);

        const pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            execl(exe_path, exe_path, child_path, pattern, NULL);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <path> <pattern>\n", argv[0]);
        return 1;
    }

    if (strlen(argv[2]) > PATTER_SIZE) {
        printf("Pattern too long\n");
        return 1;
    }
    char curr_path[PATH_MAX];
    char exe_path[PATH_MAX];
    char *pattern = argv[2];
    char buffer[PATTER_SIZE + 1];
    const size_t pattern_size = strlen(pattern);
    struct stat st;

    check_path(realpath(argv[0], exe_path), exe_path);
    check_path(realpath(argv[1], curr_path), curr_path);

    if (stat(curr_path, &st) == -1) {
        perror("stat");
        return 1;
    }

    if (S_ISDIR(st.st_mode)) search_dir(exe_path, curr_path, pattern);
    else check_pattern(curr_path, buffer, pattern, pattern_size);

    while (wait(NULL) > 0);

    return 0;
}