//
// Created by armotik on 14/03/25.
//
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void find_executable_files(const char *directory) {
    struct dirent *entry;
    struct stat file_stat;
    DIR *dp = opendir(directory);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG) {
            char filepath[1024];
            snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);

            if (stat(filepath, &file_stat) == 0) {
                if (file_stat.st_mode & S_IXUSR) {
                    printf("Executable file: %s\n", entry->d_name);
                }
            } else {
                perror("stat");
            }
        }
    }

    closedir(dp);
}