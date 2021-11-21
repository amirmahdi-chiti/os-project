#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    // printf("aaaa\n");
    int fd1, fd4;
    char myfifo1[] = "/tmp/myfifo1";
    char myfifo4[] = "/tmp/myfifo4";
    char str1[80];

    mkfifo(myfifo1, 0666);
    fd1 = open(myfifo1,O_RDONLY);
    read(fd1, str1, 80);
    close(fd1);

    printf("in decoder\n");

    mkfifo(myfifo4, 0666);
    fd4 = open(myfifo4, O_WRONLY | O_NONBLOCK);
    strcat(str1, " decoder\n");
    write(fd1, str1, strlen(str1) + 1);
    close(fd4);
    // int status;
    // exit(status);

    // printf("decoder %s\n", str1);
}