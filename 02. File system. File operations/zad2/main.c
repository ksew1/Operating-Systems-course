#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


char *reverse_buffer(char *buffer, size_t size) {
    for (size_t i = 0; i < size / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[size - i - 1];
        buffer[size - i - 1] = temp;
    }
    return buffer;
}


void reverse_file(char *in, char *out, size_t buffer_size) {
    if (buffer_size <= 0) {
        printf("Block size must be greater than 0");
        exit(1);
    }
    if (in == NULL || out == NULL) {
        printf("Input and output file names must not be null");
        exit(1);
    }
    if (strcmp(in, out) == 0) {
        printf("Input and output file names must not be the same");
        exit(1);
    }
    if (strlen(in) == 0) {
        printf("Input file name must not be empty");
        exit(1);
    }
    FILE *input;
    if ((input = fopen(in, "r")) == NULL) {
        printf("Input file does not exist");
        exit(1);
    }

    size_t end;
    FILE *output = fopen(out, "w");
    char *buffer = calloc(buffer_size + 1, sizeof(char));

    // get the size of the file
    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    fseek(input, 0, SEEK_SET);

    // calculate the number of blocks and the rest
    size_t number_of_block = size / ((size_t) buffer_size);
    size_t rest = size % ((size_t) buffer_size);

    // write the blocks
    for (size_t i = 0; i <= number_of_block; i++) {

        fseek(input, (long) (-buffer_size * i), SEEK_END);
        end = fread(buffer, sizeof(char), buffer_size, input);
        buffer[end] = 0;
        fwrite(reverse_buffer(buffer, buffer_size), sizeof(char), end, output);
    }
    // write the rest
    fseek(input, 0, SEEK_SET);
    end = fread(buffer, sizeof(char), rest, input);
    buffer[end] = 0;
    fwrite(reverse_buffer(buffer, rest), sizeof(char), end, output);

    // free the buffer and close the files
    fclose(input);
    fclose(output);
    free(buffer);
}


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Wrong number of arguments");
    }
    char *in = argv[1];
    char *out = argv[2];
    long buffer_size = BUFFER_SIZE;
    struct timespec start, end;

    clock_gettime(CLOCK_REALTIME, &start);

    reverse_file(in, out, buffer_size);

    clock_gettime(CLOCK_REALTIME, &end);
    printf("TIME: %ldns\n", end.tv_nsec - start.tv_nsec);
    return 0;
}


