#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include <sys/times.h>
#include <unistd.h>

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

double calculateTime(clock_t t1, clock_t t2) {
    return (double) (t2 - t1) / sysconf(_SC_CLK_TCK);
}

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
    clock_t t1, t2;
    struct tms *tms1 = calloc(1, sizeof(struct tms));
    struct tms *tms2 = calloc(1, sizeof(struct tms));
    char *s = calloc(MAX_LINE_LENGTH, sizeof(char));
    ArrayOfBlocks *arrayOfBlocks = NULL;

    while (1) {
        // get time before command
        t1 = times(tms1);
        printf("Enter command: ");
        if (fgets(s, MAX_LINE_LENGTH, stdin) == NULL) {
            printf("Error while reading input\n");
            continue;
        }

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
        } else if (strcmp(s, "help") == 0) {
            printf("Available commands:\n");
            printf("init <number> - initialize array of blocks with given size\n");
            printf("count <file> - count number of lines, words and characters in a file\n");
            printf("show <index> - show block with given index\n");
            printf("delete index <index> - delete block with given index\n");
            printf("destroy - destroy array of blocks\n");
            printf("help - show this help\n");
            printf("exit - exit program\n");
        } else {
            printf("Unknown command: %s\n", s);
            continue;
        }
        // get time after command
        t2 = times(tms2);

        printf("Real time: %f\n", calculateTime(t1, t2));
        printf("User time: %f\n", (double) tms2->tms_utime - tms1->tms_utime);
        printf("System time: %f\n", (double) tms2->tms_stime - tms1->tms_stime);
    }
    // free memory
    free(s);
    free(tms1);
    free(tms2);

    if (arrayOfBlocks != NULL) {
        destroyArrayOfBlocks(arrayOfBlocks);
    }
#ifdef DYNAMIC
    dlclose(handle);
#endif

    return 0;
}


