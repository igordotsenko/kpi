#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <memory.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

// Mode to file type
void mode_to_ft(int mode, char info_str[]) {
    switch((mode) & S_IFMT) {
        case S_IFDIR: // directory
            info_str[0] = 'd';
            break;
        case S_IFCHR: // character device: allow users and programs to communicate with hardware peripheral devices
            info_str[0] = 'c';
            break;
        case S_IFBLK: // block device. mostly govern hardware as hard drives, memory, etc.
            info_str[0] = 'b';
            break;
        case S_IFLNK: // symbolic link
            info_str[0] = 'l';
            break;
        case S_IFSOCK: // socket. used for communication between processes. Generally, they are used by services such as X windows, syslog and etc
            info_str[0] = 's';
            break;
        case S_IFIFO: // named pipe. allow communication between two local processes
            info_str[0] = 'p';
            break;
        default:break;
    }
}

void mode_to_str(int mode, char* mode_str) {
    strcpy(mode_str, "----------");

    mode_to_ft(mode, mode_str);

    if(mode & S_IRUSR) mode_str[1] = 'r';	// 3 bits for user
    if(mode & S_IWUSR) mode_str[2] = 'w';
    if(mode & S_IXUSR) mode_str[3] = 'x';

    if(mode & S_IRGRP) mode_str[4] = 'r';	// 3 bits for group
    if(mode & S_IWGRP) mode_str[5] = 'w';
    if(mode & S_IXGRP) mode_str[6] = 'x';

    if(mode & S_IROTH) mode_str[7] = 'r';	// 3 bits for other
    if(mode & S_IWOTH) mode_str[8] = 'w';
    if(mode & S_IXOTH) mode_str[9] = 'x';
}

void show_file_info(char *filename, struct stat *file_info) {
    char mode_str[11];
    mode_to_str(file_info->st_mode, mode_str);

    struct passwd* pswd = getpwuid(file_info->st_uid); // search the user database for an entry with a matching uid
    char* owner_name = pswd != NULL ? pswd->pw_name : "undefined";

    struct group* gr = getgrgid(file_info->st_gid);  // get group database entry for a group ID
    char* group_name = gr != NULL ? gr->gr_name : "undefined";

    printf("%s ", mode_str);
    printf("%d ", file_info->st_nlink); // get number of links
    printf("%s ", owner_name);
    printf("%s ", group_name);
    printf("%8ld ", (long)file_info->st_size); // size in bytes
    printf("%.12s ", ctime(&file_info->st_mtime)); // modification time
    printf("%llu ", file_info->st_ino); // get i-node
    printf("%s\n", filename);
}

void print_file_stats(char *absolutePath, char *filename) {
    struct stat file_info;

    if (lstat(absolutePath, &file_info) == -1) {
        perror(absolutePath);
    } else {
        show_file_info(filename, &file_info);
    }
}

char* file_abs_path(char* dir_path, struct dirent* dir_entry) {
    char* abs_path =(char *) malloc(strlen(dir_path) + strlen(dir_entry->d_name) + 2);
    if (abs_path) {
        strcpy(abs_path, dir_path);
        strcat(abs_path, "/");
        strcat(abs_path, dir_entry->d_name);
        return abs_path;
    } else {
        printf("Cannot allocate memory");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    DIR* dir;
    struct dirent* dir_entry;
    struct stat mystat;

    char* dir_path = argc > 1 ? argv[1] : "."; // Determine path of directory to open

    printf("dir_path %s\n", dir_path);


    if ((dir = opendir(dir_path)) == NULL) {
        printf("Cannot open %s\n", dir_path);
        return 0;
    }

    while ((dir_entry = readdir(dir)) != NULL) {
        char* abs_file_path = file_abs_path(dir_path, dir_entry);
        print_file_stats(file_abs_path(dir_path, dir_entry), dir_entry->d_name);
        free(abs_file_path);
    }
    closedir(dir);
}
