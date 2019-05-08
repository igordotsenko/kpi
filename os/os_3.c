#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

#define READING 0
#define WRITING 1

void open_pipe(int *fd) {
    if (pipe(fd)==-1) {
        fprintf(stderr, "Failed" );
        exit(1);
    }
}

void write_file(FILE* file, int fd[2]) {
    char buffer[100];
    while (!feof(file)) {
        fgets(buffer, sizeof(buffer), file);
        write(fd[1], buffer, sizeof(buffer));
    }
}

void print_pipe_output(int pipe[2]) {
    char out[1000];

    if (read(pipe[READING], out, 1000) > 0) {
        printf("%s", out);
    }
    printf("\n");
}

int count_lines(const char input[100]) {
    int count = 0;

    for (int i = 0 ; i < 100; i++) {
        if (input[i] == '\n') {
            count += 1;
        } else if (input[i] == '\0') {
            return count;
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    printf("Start 1\n");
    if (argc < 2) {
        printf("Pass file path");
        exit(1);
    }

    printf("Start 2\n");

    int parent_to_child[2];  // File descriptor for the first pipe: send input string from parent to child
    int child_to_parent[2];  // File descriptor for the second pipe: send from child to parent
    char* input_file_path = argv[1];
    FILE* input_file = input_file = fopen(input_file_path, "r");
    int status;
    pid_t pid = 0;

    printf("Open files\n");
    if (input_file == NULL) {
        printf("Cannot open file: %s", input_file_path);
        exit(1);
    }

    open_pipe(parent_to_child);
    open_pipe(child_to_parent);
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Forking failed" );
        return 1;
    } else if (pid > 0) { // Parent process
        close(parent_to_child[READING]);
        close(child_to_parent[WRITING]);
        write_file(input_file, parent_to_child);
        close(parent_to_child[WRITING]);

        if (waitpid(pid, &status, 0) == -1) {
            printf("Error on waitpid call\n");
            exit(1);
        }

        print_pipe_output(child_to_parent);
        close(child_to_parent[READING]);
        fclose(input_file);
    } else {  // child process
        close(child_to_parent[READING]);
        close(parent_to_child[WRITING]);

        char c;
        int lines_count = -1;
        char child_buffer[100];
        while (read(parent_to_child[READING], child_buffer, 100) > 0) {
            lines_count += count_lines(child_buffer);
        }
        close(parent_to_child[READING]);

        char output[10];
        sprintf(output, "%d", lines_count);
        write(child_to_parent[WRITING], output, strlen(output));
        close(child_to_parent[WRITING]);
        exit(0);
    }
}