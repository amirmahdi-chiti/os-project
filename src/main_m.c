#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){

    // printf ("here");
    // FIFO file path
    char myfifo1[] = "/tmp/myfifo1";
    char myfifo2[] = "/tmp/myfifo2";
    char myfifo3[] = "/tmp/myfifo3";
    char myfifo4[] = "/tmp/myfifo4";
    char myfifo5[] = "/tmp/myfifo5";
    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo1, 0666);
    mkfifo(myfifo2, 0665);
    mkfifo(myfifo3, 0664);
    int fd1,fd2,fd3,fd4,fd5;
    // Open FIFO for write only
    char arr[1000] = "test";
    //  Write the input arr2ing on FIFO
    pid_t p1, p2=-1, p3=-1; 
    p1 = fork();

    if (p1 > 0) {
        fd1 = open(myfifo1, O_WRONLY);
        write(fd1, arr, strlen(arr)+1);
        close(fd1);

        fd2 = open(myfifo2, O_WRONLY);
        write(fd2, arr, strlen(arr) + 1);
        close(fd2);

        fd3 = open(myfifo3, O_WRONLY);
        write(fd3, arr, strlen(arr) + 1);
        close(fd3);
    } 
  
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
        read(fd1, str1, 80);
        close(fd1);
        p2 = fork();
        if (p2 > 0) {
            mkfifo(myfifo4, 0666);
            fd4 = open(myfifo4,O_WRONLY);
            strcat(str1,"fork1");
            write(fd4,str1,strlen(str1)+1);
            close(fd4);
        }
        if (p2 < 0)
        {
        fprintf(stderr, "fork2 Failed" );
        return 1;
        }
        else if (p2==0)
        {
            // printf("here\n");
            char str2[80];
            char str3[80];
            mkfifo(myfifo2, 0666);
            fd2 = open(myfifo2,O_RDONLY);
            read(fd2, str2, 80);
            close(fd2);
            mkfifo(myfifo4, 0666);
            fd4 = open(myfifo4,O_RDONLY);
            read(fd4, str3, 80);
            printf("%s\n", str3);
            close(fd4);
            p3 = fork();
            if (p3 > 0) {
                mkfifo(myfifo5, 0666);
                fd5 = open(myfifo5,O_WRONLY);
                strcat(str2,str3);
                write(fd5,str2,strlen(str2)+1);
                close(fd5);
            }
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
                read(fd3, str4, 80);
                close(fd3);
                mkfifo(myfifo5, 0666);
                fd5 = open(myfifo5,O_RDONLY); 
                read(fd5,str5,80);
                close(fd5);
                // strcat(str4,str5);
                printf("%s\n",strcat(str4,str5));
            }
        
        }
        

    }
    
}