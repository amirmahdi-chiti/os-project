#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
    pid_t p; 
     p = fork();
  
    if (p < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;
    }
    else if (p>0)
    {
        int fd;

    // FIFO file path
    char * myfifo = "/tmp/myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666);

    char arr1[80], arr2[80];
        while (1)
        {
            // Open FIFO for write only
            fd = open(myfifo, O_WRONLY);

            // Take an input arr2ing from user.
            // 80 is maximum length
            fgets(arr2, 80, stdin);
            // strcpy(arr2,"slama\nkhobi");
            
            arr2[strlen(arr2)-1] = '\0';
            // Write the input arr2ing on FIFO
            // and close it
            write(fd, arr2, strlen(arr2)+1);
            close(fd);

            // Open FIFO for Read only
            fd = open(myfifo, O_RDONLY);

            // Read from FIFO
            read(fd, arr1, sizeof(arr1));

            // Print the read message
            printf("User2: %s\n", arr1);
            close(fd);
        }
    
    }
    else{
        int fd1;

    // FIFO file path
    char * myfifo = "/tmp/myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(myfifo, 0666);

    char str1[80], str2[80];
        while (1)
        {
            // First open in read only and read
            fd1 = open(myfifo,O_RDONLY);
            read(fd1, str1, 80);

            // Print the read string and close
         //   printf("User1: %s\n", str1);
            close(fd1);

            // Now open in write mode and write
            // string taken from user.
            fd1 = open(myfifo,O_WRONLY);
           // fgets(str2, 80, stdin);
           strcat(str1,"Guys");
            write(fd1, str1, strlen(str1)+1);
            close(fd1);
        }
    
    }
    

}