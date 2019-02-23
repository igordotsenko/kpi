#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <memory.h>


#define MAXLINE 4096


void server(int readfd, int writefd)
{
    int fd;
    ssize_t n;
    char buff[MAXLINE+1], msg[MAXLINE+1];

/* зчитування повного імені файлу з каналу IPC */

    if ((n = read(readfd, buff, MAXLINE)) < 0)
    {
        snprintf(msg, sizeof(msg), "Сервер: помилка читання повного імені файлу зканалу IPC: %s\n", strerror(errno));
        write(writefd, msg, strlen(msg));
        exit(1);
    }
    if (n == 0)
    {
        snprintf(msg, sizeof(msg), "Сервер: зчитано порожнє ім’я файлу, завершення роботи\n");
                write(writefd, msg, strlen(msg));
        exit(1);
    }
    buff[n] = '\0'; /* додаємо ознаку кінця рядка до повного імені */
    if ((fd = open(buff, O_RDONLY)) < 0)
    { /* повідомляємо клієнту про помилку відкриття файлу */
        snprintf(msg, sizeof(msg), "Сервер: помилка відкриття файлу %s: %s\n", buff,
                 strerror(errno));
        write(writefd, msg, strlen(msg));
        exit(1);
    }
    else /* файл успішно відкрито; копіюємо його в канал IPC */
    {
        while ((n = read(fd, msg, MAXLINE)) > 0)
            if (write(writefd, msg, n) != n)
            {
                snprintf(msg, sizeof(msg), "Сервер: помилка запису вмісту файлу %s в канал IPC: %s\n", buff, strerror(errno));
                write(writefd, msg, strlen(msg));
                exit(1);
            }
        if (n < 0)
        {
            snprintf(msg, sizeof(msg), "Сервер: помилка читання вмісту файлу %s: %s\n", buff, strerror(errno));
                    write(writefd, msg, strlen(msg));
            exit(1);
        }
        close(fd);
    }
}
void client(int readfd, int writefd)
{
    size_t len;
    ssize_t n;
    char buff[MAXLINE];
/* зчитування повного імені файлу зі стандартного потоку введення */
    if (fgets(buff, MAXLINE, stdin) == NULL)
    {
        fprintf(stderr, "Клієнт: помилка читання повного імені файлу зі стандартного потоку введення\n");
        exit(1);
    }
    len = strlen(buff); /* fgets() гарантує завершальний нульовий байт */
    if (buff[len-1] == '\n')
        len--; /* вилучення символу переведення рядка (якщо є) */
    if (len == 0)
    {
        fprintf(stderr, "Клієнт: введено порожнє ім’я файлу, завершення роботи\n");
        exit(1);
    }
/* запис повного імені файлу в канал IPC */
    if (write(writefd, buff, len) < 0)
    {
        fprintf(stderr, "Клієнт: помилка запису повного імені файлу в канал IPC: %s\n", strerror(errno));
        exit(1);
    }
/* зчитування з каналу IPC, запис в стандартний потік виведення */
    while ((n = read(readfd, buff, MAXLINE)) > 0)
        if (write(STDOUT_FILENO, buff, n) != n)
        {
            fprintf(stderr, "Клієнт: помилка запису вмісту файлу в стандартний потік виведення : %s\n", strerror(errno));
            exit(1);
        }
    if (n < 0)
    {
        fprintf(stderr, "Клієнт: помилка читання вмісту файлу з каналу IPC: %s\n", strerror(errno));
        exit(1);
    }
}
int main(int argc, char **argv)
{
    int pipe1[2], pipe2[2], status;
    pid_t childpid;
    if (pipe(pipe1) == -1) /* створення двох каналів */
    {
        fprintf(stderr, "Неможливо створити канал pipe1: %s\n");
        exit(1);
    }
    if (pipe(pipe2) == -1)
    {
        fprintf(stderr, "Неможливо створити канал pipe2: %s\n", strerror(errno));
        exit(1);
    }


    if ((childpid = fork()) == -1)
    {
        fprintf(stderr, "Помилка виклику функції fork: %s\n", strerror(errno));
        exit(1);
    }

    if (childpid == 0) /* дочірній процес */
    {
        close(pipe1[1]);
        close(pipe2[0]);
        server(pipe1[0], pipe2[1]);
        exit(0);
    }
    close(pipe1[0]); /* батьківський процес */
    close(pipe2[1]);
    client(pipe2[0], pipe1[1]);
    if (waitpid(childpid, &status, 0) == -1)
    { /* очікування завершення дочірнього процесу */
        fprintf(stderr, "Помилка виклику функції waitpid: %s\n", strerror(errno));
        exit(1);
    }
    if (status == 0)
        fprintf(stderr, "Копіювання файлу успішно завершено\n");
    exit(0);
}