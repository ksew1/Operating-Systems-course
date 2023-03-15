#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>


int main() {
    DIR *dir;
    struct stat st;
    struct dirent *ent;
    long long size = 0;

    if ((dir = opendir(".")) == NULL) {
        perror("Could not open directory");
        return 1;
    }

    while ((ent = readdir(dir)) != NULL) {
        stat(ent->d_name, &st);
        if (!S_ISDIR(st.st_mode)) {
            printf("%s %ld bytes \n", ent->d_name, st.st_size);
            size += st.st_size;
        }
    }
    printf("Total size: %lld bytes \n", size);
    closedir(dir);
    return 0;
}
