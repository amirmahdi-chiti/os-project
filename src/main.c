#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){

    // FIFO file path
    char * myfifo1 = "/tmp/myfifo1";
    char * myfifo2 = "/tmp/myfifo2";
    char * myfifo3 = "/tmp/myfifo3";
    char * myfifo4 = "/tmp/myfifo4";
    char * myfifo5 = "/tmp/myfifo5";
    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo1, 0666);
    mkfifo(myfifo2, 0666);
    mkfifo(myfifo3, 0666);
    int fd1,fd2,fd3,fd4,fd5;
    // Open FIFO for write only
    fd1 = open(myfifo1, O_WRONLY);
    fd2 = open(myfifo2, O_WRONLY);
    fd3 = open(myfifo3, O_WRONLY);
    char arr[] = "test";
     // Write the input arr2ing on FIFO
     // and close it
    write(fd1, arr, strlen(arr)+1);
    close(fd1);
    write(fd2, arr, strlen(arr)+1);
    close(fd2);
    write(fd3, arr, strlen(arr)+1);
    close(fd3);
    pid_t p1,p2,p3; 
    p1 = fork();
  
    if (p1 < 0)
    {
        fprintf(stderr, "fork1 Failed" );
        return 1;
    }
    else if (p1==0)
    {
        char str1[80];
        mkfifo(myfifo1, 0666);
        fd1 = open(myfifo1,O_RDONLY);
        mkfifo(myfifo4, 0666);
        fd4 = open(myfifo4,O_WRONLY);
        read(fd1, str1, 80);
        close(fd1);
        strcat(str1,"fork1");
        write(fd4,str1,strlen(str1)+1);
        close(fd4);
        p2 = fork();
        if (p2 < 0)
        {
        fprintf(stderr, "fork2 Failed" );
        return 1;
        }
        else if (p2==0)
        {
            char str2[80];
            char str3[80];
            mkfifo(myfifo2, 0666);
            fd2 = open(myfifo2,O_RDONLY);
            mkfifo(myfifo4, 0666);
            fd4 = open(myfifo4,O_RDONLY);
            mkfifo(myfifo5, 0666);
            fd5 = open(myfifo5,O_WRONLY);
            read(fd2, str2, 80);
            close(fd2);
            read(fd4, str3, 80);
            close(fd4);
            write(fd5,strcat(str2,str3),strlen(str2)+1);
            close(fd5);
            p3 = fork();
            if (p3 < 0)
            {
                fprintf(stderr, "fork 3 Failed" );
                return 1;
            }
            else if (p3==0)
            {
                char str4[80];
                char str5[80];

                mkfifo(myfifo3, 0666);
                fd3 = open(myfifo3,O_RDONLY);
                mkfifo(myfifo5, 0666);
                fd5 = open(myfifo5,O_RDONLY);
                read(fd3, str4, 80);
                close(fd3);
                read(fd5,str5,80);
                close(fd5);
                printf("%s",strcat(str4,str5));
            }
        
        }
        

    }
    
}