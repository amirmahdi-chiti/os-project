#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

void findSubStr(char[], int, int, char[]);

struct Finder
{
    int start;
    int end;
    char str[500];
};


char* finder(char processString[], char boundsString[]) {
    // "Finder"s which will be used to store the bounds. in the first
    // loop just bounds and in the second loop the string will be 
    // extracted completely
    struct Finder finders[10000];

    // Controling varriables which help to count and store bounds
    char number[10000] = "";
    int boundCnt = 0;
    // In this loop we extract the bounds and store them in a
    // "Finder" object 
    for (int i = 0; boundsString[i] != '\0'; i++) {
        if (boundsString[i] >= '0' && boundsString[i] <= '9') {
            // That we are finding a number
            strncat(number, &boundsString[i], 1);
        }
        if (boundsString[i] == ' ') { 
            // In the next line we convert the number(first one) from string to integer
            // and then set it as the beginning of the bound.
            int startNumber = atoi(number);
            finders[boundCnt].start = startNumber;
            // In the next line we empty the number string
            memset(number, 0, strlen(number));
        }
        if (boundsString[i] == '$') {
            // As we stated above, to have the beginning of the bound we used stated codes
            // and now to have the end of the bound we should have the last number before $ sign
            int length = atoi(number);
            finders[boundCnt].end = length + finders[boundCnt].start;
            // In the next line we empty the number string 
            memset(number, 0, strlen(number));
            char str[10000] = "";
            // In the next function we find the substring and that will be stored in str
            findSubStr(processString, finders[boundCnt].start, finders[boundCnt].end, str);
            int k;
            // In the following code we copy str to the finder's str
            for (k = 0; str[k] != '\0'; k++)
                finders[boundCnt].str[k] = str[k];
            finders[boundCnt].str[k] = '\0';
            boundCnt++;
        }
    }

    char* finalStr = "\0";

    for (int i = 0; i < boundCnt; i++) {
        strcat(finalStr, finders[i].str);
        strcat(finalStr, ",");
    }

    finalStr[strlen(finalStr)] = '\0';

    return finalStr;
}

int main() {
    char boundsString[10000];
    char proccessString[10000];
    
    char fromParent[] = "/tmp/fifo2";
    char fromDecoder[] = "/tmp/fifo4";
    char toPlacer[] = "/tmp/fifo5";

    int fd;

    char outParent[1000];
	mkfifo(fromParent, 0666);
	fd = open(fromParent, O_RDONLY);
	read(fd, outParent, 1000);
	close(fd);

    char outDecoder[1000];
	mkfifo(fromDecoder, 0666);
	fd = open(fromDecoder, O_RDONLY);
	read(fd, outDecoder, 1000);
	close(fd);

    char* toPlacerStr = finder(outDecoder, outParent);

    mkfifo(toPlacer, 0666);
    fd = open(toPlacer, O_WRONLY);
    write(fd, toPlacerStr, strlen(toPlacerStr) + 1);
    close(fd);
    
    return 0;

}

// In the next function we find the substring and that will be stored in str
void findSubStr(char str[], int s, int e, char result[]) {
    for (int i = s; i <= e && str[i] != '\0'; i++)
    strncat(result, &str[i], 1);
}