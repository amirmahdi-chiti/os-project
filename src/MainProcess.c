#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

void readFile(char*, char[]);
char** splitInput(char*);

int main() {
    char input[1000];
    readFile("input.txt", input);
    char** splits = splitInput(input);
    char fifos[][1000] = { 
        "/tmp/fifo1",
        "/tmp/fifo2",
        "/tmp/fifo3",
    };

    pid_t decoder, finder, placer;

    decoder = fork();
    if (decoder == 0) {
        char *args[] = {"./decoder", NULL};
		execvp(args[0], args);
    }

    finder = fork();
    if (finder == 0) {
        char *args[] = {"./finder", NULL};
		execvp(args[0], args);
    }

    placer = fork();
    if (placer == 0) {
        char *args[] = {"./placer", NULL};
		execvp(args[0], args);
    }

    int fd;
	mkfifo(fifos[0], 0666);
	fd = open(fifos[0], O_WRONLY);
	write(fd, splits[0], strlen(splits[0]) + 1);
	close(fd);

	mkfifo(fifos[1], 0666);
	fd = open(fifos[1], O_WRONLY);
	write(fd, splits[1], strlen(splits[1]) + 1);
	close(fd);

	mkfifo(fifos[2], 0666);
	fd = open(fifos[2], O_WRONLY);
	write(fd, splits[2], strlen(splits[2]) + 1);
	close(fd);

    char outPlacer[1000];

	mkfifo(fifos[2], 0666);
	fd = open(fifos[2], O_RDONLY);
	read(fd, outPlacer, 1000);
	close(fd);

    printf("result is:%s\n", outPlacer);

}

void readFile(char* filename, char outRead[]){
//const char* filename = "input.txt";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return;
    }

    // read one character at a time and
    // display it to the output
    char out[1000];
    char ch;
    int i = 0;
    while ((ch = fgetc(fp)) != EOF)
        out[i++] = ch;

    out[i] = '\0';
    outRead[0] = '\0';

    strcpy(outRead, out);

    // close the file
    fclose(fp);
}

char** splitInput(char s[]){
    int end1=0,end2=0;
    int count = 0;
    char **strArr=(char**)malloc(sizeof(char*)*3);
    for(int i=0;i<3;i++)
    {
        strArr[i]=(char*)malloc(1000);
    }
    for(int i = 0;i<strlen(s);i++){
        if(s[i]=='#'&& s[i+1]=='#'&&s[i+2]=='#'){
            if (count==0)
            {
                end1 = i;
                count++;
            }
            else if (count==1)
            {
                end2 = i;
                break;
            }
            
        }
    }
    //printf("end 1 = %d\n", end1);
    //printf("end 2 = %d\n", end2);
    int k;
    for (int i = 0; i < end1; i++)
    {
        strArr[0][i] = s[i];
    }
    strArr[0][end1] = '\0';
    k = 0;
    for (int i = end1 + 3; i < end2; i++, k++)
    {
        strArr[1][k] = s[i];
        // printf("%c", strArr[1][i]);
    }
    // printf("%c\n", strArr[1][2]);
    strArr[1][k] = '\0';
    k = 0;
    for (int i = end2 + 3; i < strlen(s); i++, k++)
    {  
        strArr[2][k] = s[i];
    }
    strArr[2][k] = '\0';
    return strArr;
}