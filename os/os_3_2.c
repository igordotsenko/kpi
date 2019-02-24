#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <memory.h>

#define BUFFER_SIZE 100

void run_command() {
    char   result[BUFFER_SIZE];
    FILE*  pipe;

    // shall create a pipe between the calling program and the executed command,
    // and shall return a pointer to a stream that can be used to either read from or write to the pipe.
    pipe = popen("who", "w");
    if (pipe == NULL) {
        printf("Error open pipe");
        exit(1);
    }

    while (fgets(result, BUFFER_SIZE, pipe) != NULL) {
        printf("%s", result);
    }

    pclose(pipe);
}

char* email_command(const char* address) {
    char* email_template = "echo \"Congrats\" | mail -s \"Congrats\" ";
    char* command = malloc(sizeof(email_template) + sizeof(address) + 10);

    strcpy(command, email_template);
    strcat(command, address);

    printf("Running command : %s\n", command);
    return command;
}

void send_mail(int argc, char **argv) {
    FILE*  pipe;

    for (int i = 1; i < argc; i++) {
        if (pipe = popen(email_command(argv[i]), "w") == NULL) {
            printf("Error opening pipe on mail sending to %s", argv[i]);
            exit(1);
        }
    }
    pclose(pipe);
}

int main(int argc, char** argv) {
    run_command();
    if (argc < 2) {
        printf("%s\n", "Pass e-mail address for e-mail sending");
        exit(0);
    }
    send_mail(argc, argv);
    return 0;
}
