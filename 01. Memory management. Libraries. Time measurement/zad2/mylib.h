#ifndef mylib_h
#define mylib_h
#define MAX_LINE_LENGTH 200


typedef struct Block {
    char *file;
    int numberOfLines;
    int numberOfWords;
    int numberOfChars;
} Block;

typedef struct ArrayOfBlocks {
    int size;
    int currentIndex;
    Block *blocks;
} ArrayOfBlocks;

ArrayOfBlocks *createArrayOfBlocks(int size);

void count(ArrayOfBlocks *arrayOfBlocks, char *name);

Block *returnBlock(ArrayOfBlocks *arrayOfBlocks, int index);

void removeBlock(ArrayOfBlocks *arrayOfBlocks, int index);

void destroyArrayOfBlocks(ArrayOfBlocks *arrayOfBlocks);

#endif //mylib_h