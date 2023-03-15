#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error(char *message) {
    printf("%s", message);
    exit(1);
}

void checkIfArrayIsNull(ArrayOfBlocks *arrayOfBlocks) {
    if (arrayOfBlocks == NULL) {
        error("Array is null\n");
    }
}


ArrayOfBlocks *createArrayOfBlocks(int size) {
    ArrayOfBlocks *arrayOfBlocks = (ArrayOfBlocks *) calloc(1, sizeof(ArrayOfBlocks));
    arrayOfBlocks->size = size;
    arrayOfBlocks->currentIndex = -1;
    arrayOfBlocks->blocks = (Block *) calloc(size, sizeof(Block));
    return arrayOfBlocks;
}


void count(ArrayOfBlocks *arrayOfBlocks, char *name) {
    checkIfArrayIsNull(arrayOfBlocks);
    if (access(name, F_OK) == -1) {
        error("File does not exist\n");
    }
    if (arrayOfBlocks->currentIndex == arrayOfBlocks->size - 1) {
        error("Array is full\n");
    }
    arrayOfBlocks->currentIndex++;
    arrayOfBlocks->blocks[arrayOfBlocks->currentIndex].file = (char *) calloc(strlen(name) + 1, sizeof(char));

    char *command = (char *) calloc(strlen(name) + 25, sizeof(char));
    strcpy(command, "wc ");
    strcat(command, name);
    strcat(command, " > /tmp/mylibtmp.txt");
    if (system(command) == -1) {
        error("Failed to execute command\n");
    }
    FILE *file = fopen("/tmp/mylibtmp.txt", "r");
    if (file == NULL) {
        error("Failed to open file\n");
    }
    char *line = (char *) calloc(MAX_LINE_LENGTH, sizeof(char));
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL) {
        error("Failed to read line\n");
    }
    char *token = strtok(line, " ");
    arrayOfBlocks->blocks[arrayOfBlocks->currentIndex].numberOfLines = atoi(token);
    token = strtok(NULL, " ");
    arrayOfBlocks->blocks[arrayOfBlocks->currentIndex].numberOfWords = atoi(token);
    token = strtok(NULL, " ");
    arrayOfBlocks->blocks[arrayOfBlocks->currentIndex].numberOfChars = atoi(token);
    token = strtok(NULL, " ");
    strcpy(arrayOfBlocks->blocks[arrayOfBlocks->currentIndex].file, token);
    free(line);
    free(command);
    fclose(file);
    remove((const char *) file);
}

Block *returnBlock(ArrayOfBlocks *arrayOfBlocks, int index) {
    if (index < 0 || index > arrayOfBlocks->currentIndex) {
        error("Invalid index\n");
    }
    return &arrayOfBlocks->blocks[index];
}

void removeBlock(ArrayOfBlocks *arrayOfBlocks, int index) {
    checkIfArrayIsNull(arrayOfBlocks);
    if (index < 0 || index > arrayOfBlocks->currentIndex) {
        error("Invalid index\n");
    }
    free(arrayOfBlocks->blocks[index].file);
    for (int i = index; i < arrayOfBlocks->currentIndex; i++) {
        arrayOfBlocks->blocks[i] = arrayOfBlocks->blocks[i + 1];
    }
    arrayOfBlocks->currentIndex--;
}

void destroyArrayOfBlocks(ArrayOfBlocks *arrayOfBlocks) {
    checkIfArrayIsNull(arrayOfBlocks);
    for (int i = 0; i <= arrayOfBlocks->currentIndex; i++) {
        free(arrayOfBlocks->blocks[i].file);
    }
    free(arrayOfBlocks->blocks);
    free(arrayOfBlocks);
}



