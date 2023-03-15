#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include <sys/times.h>
#include <time.h>

#ifdef DYNAMIC
#include <dlfcn.h>

void *loadFunction(void *handle, char *name) {
    void *libfun = dlsym(handle, name);
    if (!libfun) {
        printf("Error: %s\n", dlerror());
        exit(1);
    }
    return libfun;
}

#endif


void displayBlock(Block *block) {
    if (block != NULL) {
        printf("Number of lines: %d\n", block->numberOfLines);
        printf("Number of words: %d\n", block->numberOfWords);
        printf("Number of characters: %d\n", block->numberOfChars);
        printf("File name: %s\n", block->file);
    }
}

int main() {
#ifdef DYNAMIC
    void *handle = dlopen("./libmylib.so", RTLD_LAZY);
    if (!handle) {
        printf("Error: %s\n", dlerror());
        exit(1);
    }
    ArrayOfBlocks *(*createArrayOfBlocks)(int) = loadFunction(handle, "createArrayOfBlocks");
    void (*count)(ArrayOfBlocks *, char *) = loadFunction(handle, "count");
    Block *(*returnBlock)(ArrayOfBlocks *, int) = loadFunction(handle, "returnBlock");
    void (*removeBlock)(ArrayOfBlocks *, int) = loadFunction(handle, "removeBlock");
    void (*destroyArrayOfBlocks)(ArrayOfBlocks *) = loadFunction(handle, "destroyArrayOfBlocks");
#endif
    // init variables
    int n;
    struct tms tms1, tms2;
    ArrayOfBlocks *arrayOfBlocks = NULL;
    char *s = calloc(MAX_LINE_LENGTH, sizeof(char));
    struct timespec timespec_1, timespec_2;
    while (1) {
        // get time before command
        clock_gettime(CLOCK_REALTIME, &timespec_1);
        times(&tms1);

        if (fgets(s, MAX_LINE_LENGTH, stdin) == NULL) {
            printf("Error while reading input\n");
            continue;
        }
        printf("COMMAND: %s", s);
        // remove newline character
        s[strcspn(s, "\n")] = 0;
        if (strcmp(s, "exit") == 0) {
            break;
        } else if (strncmp(s, "init", 4) == 0) {
            n = atoi(s + 5);
            if (arrayOfBlocks != NULL) {
                printf("Array already initialized\n");
                continue;
            }
            if (n < 0) {
                printf("Invalid number: %s\n", s + 5);
                continue;
            }
            arrayOfBlocks = createArrayOfBlocks(n);
        } else if (strncmp(s, "count", 5) == 0) {
            count(arrayOfBlocks, s + 6);
        } else if (strncmp(s, "show", 4) == 0) {
            n = atoi(s + 5);
            if (n < 0) {
                printf("Invalid number: %s\n", s + 5);
                continue;
            }
            displayBlock(returnBlock(arrayOfBlocks, n));
        } else if (strncmp(s, "delete index", 12) == 0) {
            n = atoi(s + 13);
            if (n < 0) {
                printf("Invalid number: %s\n", s + 13);
                continue;
            }
            removeBlock(arrayOfBlocks, n);
        } else if (strcmp(s, "destroy") == 0) {
            destroyArrayOfBlocks(arrayOfBlocks);
            arrayOfBlocks = NULL;
        } else {
            printf("Unknown command: %s\n", s);
            continue;
        }
        // get time after command

        clock_gettime(CLOCK_REALTIME, &timespec_2);
        times(&tms2);
        printf("EXECUTION TIME:\n");
        printf("REAL: %ldns\n", timespec_2.tv_nsec - timespec_1.tv_nsec);
        printf("USER: %ldticks\n", tms2.tms_cutime - tms1.tms_cutime);
        printf("SYSTEM: %ldticks\n\n", tms2.tms_cstime - tms1.tms_cstime);
    }
    // free memory
    free(s);
    if (arrayOfBlocks != NULL) {
        destroyArrayOfBlocks(arrayOfBlocks);
    }
#ifdef DYNAMIC
    dlclose(handle);
#endif

    return 0;
}


