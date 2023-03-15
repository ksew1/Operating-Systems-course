#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifdef USESYS
#include <fcntl.h>
#include <unistd.h>


void replace(char c1, char c2, char *input, char *output) {
    int inputFile = open(input, O_RDONLY);
    int outputFile = open(output, O_WRONLY | O_CREAT, 0644);
    lseek(inputFile, 0, SEEK_SET);
    char c;
    while (read(inputFile, &c, sizeof(char)) == 1) {
        if (c == c1) {
            c = c2;
        }

        if(write(outputFile, &c, sizeof(char)) != 1) {
            perror("write");
            exit(1);
        }

    }
    close(inputFile);
    close(outputFile);
}
#else

void f_replace(char c1, char c2, char *input, char *output) {
    FILE *inputFile = fopen(input, "r");
    FILE *outputFile = fopen(output, "w");
    fseek(inputFile, 0, SEEK_SET);

    char c;
    while (fread(&c, sizeof(char), 1, inputFile) == 1) {
        if (c == c1) {
            c = c2;
        }
        if (fwrite(&c, sizeof(char), 1, outputFile) != 1) {
            perror("write");
            exit(1);
        }
    }
    fclose(inputFile);
    fclose(outputFile);
}

#endif

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Wrong number of arguments");
        return 1;
    }
    char c1 = *argv[1];
    char c2 = *argv[2];
    char *input = argv[3];
    char *output = argv[4];
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
#ifdef USESYS
    replace(c1, c2, input, output);
#else
    f_replace(c1, c2, input, output);
#endif
    clock_gettime(CLOCK_REALTIME, &end);
    printf("TIME: %ldns\n", end.tv_nsec - start.tv_nsec);

    return 0;
}
