#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>


/*
 *   Procedure for recursively show files in a given directory
*/

void listFilesRecursively(char *basePath) {
    char path[1000];
    struct dirent *dp;
    struct stat fileStat;
    char buffer[80];
    DIR *dir = opendir(basePath);
    if (!dir) {
        return;
    }
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            sprintf(path, "%s/%s", basePath, dp->d_name);
            if (stat(path, &fileStat) == 0) {
                strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&fileStat.st_mtime));
                printf("%s %ld %s\n", path, fileStat.st_size, buffer);
            }
            if (dp->d_type == DT_DIR) {
                listFilesRecursively(path);
            }
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {

  char basePath[1000];

  if (argc > 1) {
        snprintf(basePath, sizeof(basePath), "%s", argv[1]);
    }
    //printf("basePath: %s\n", basePath);
    listFilesRecursively(basePath);
    return 0;
}
