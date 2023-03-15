#include <stdio.h>
#include <ftw.h>

long long size = 0;

int search(const char *path, const struct stat *st, int flag) {
    if (flag == FTW_F) {
        printf("%s %ld\n", path, st->st_size);
        size += st->st_size;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments");
        return 1;
    }

    char *path = argv[1];

    if (ftw(path, search, 1) == -1) {
        perror("ftw");
        return 1;
    }
    printf("Total size: %lld\n", size);
    return 0;
}
