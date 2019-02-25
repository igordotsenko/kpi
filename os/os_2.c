#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>


long get_dir_size(char* dir_path);

int is_not_current_or_parent_dir(struct dirent* dir_info) {
    return strcmp(dir_info->d_name, ".") != 0 && strcmp(dir_info->d_name, "..") != 0;
}

long get_file_size(char* file_path) {
    long total_size = 0;
    struct stat file_stat;
    int status = lstat(file_path, &file_stat);

    if (status == -1) {
        printf("Error getting size for %s\n", file_path);
        return 0;
    }
    if (S_ISDIR(file_stat.st_mode)) {
        total_size += get_dir_size(file_path);
    } else if (S_ISREG(file_stat.st_mode)) {
        total_size += file_stat.st_size;
        return total_size;
    } else {
        return 0;
    }
    return total_size;
}

long get_dir_size(char* dir_path) {
    DIR* current_dir;
    struct dirent* dir_info;
    current_dir = opendir(dir_path);
    int size = 0;

    if (current_dir != NULL) {
        while ((dir_info = readdir(current_dir)) != NULL) {
            if (is_not_current_or_parent_dir(dir_info)) {
                char* next_file_path =(char *) malloc(strlen(dir_path) + strlen(dir_info->d_name) + 2);

                strcpy(next_file_path, dir_path);
                strcat(next_file_path, "/");
                strcat(next_file_path, dir_info->d_name);

                size += get_file_size(next_file_path);
            }
        }
        closedir(current_dir);
    }

    return size;
}

int main(int argc, char* argv[]) {
    char* file_path;
    char absolute_path [PATH_MAX+1];

    // Realpath: derive, from the pathname pointed to by file_name, an absolute pathname that names the same file,
    // whose resolution does not involve '.', '..', or symbolic links
    if (argc == 1) {
        file_path = ".";
        printf("%s %ld\n", realpath(file_path, absolute_path), get_file_size(file_path));
    } else {
        for (int i = 1; i < argc; i++) {
            file_path = argv[i];
            printf("%s %ld\n", realpath(file_path, absolute_path), get_file_size(file_path));
        }
    }

    return 0;
}
