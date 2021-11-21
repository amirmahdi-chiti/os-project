
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

char* replaceWord(const char* s,
				const char* newW)
{
	char* result;
	int i, cnt = 0;
    const char* oldW = "$";
	int newWlen = strlen(newW);
	int oldWlen = strlen(oldW);

	
	for (i = 0; s[i] != '\0'; i++) {
		if (strstr(&s[i], oldW) == &s[i]) {
			cnt++;

			
			i += oldWlen - 1;
		}
	}

	result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);

	i = 0;
	while (*s) {
	
		if (strstr(s, oldW) == s) {
			strcpy(&result[i], newW);
			i += newWlen;
			s += oldWlen;
           
            break;
		}
		else
			result[i++] = *s++;
	}
    while (*s)
    {
    result[i++] = *s++;
    }
    
	result[i] = '\0';
	return result;
}
char* replaceAllWord(char newWord[][100],const char* s, int size){
    for (int i = 0; i < size; i++)
    {
        char* n = newWord[i];
        //char* result = NULL;
        s = replaceWord(s,n);
        //printf("Result: %s\n", result);
        //strcpy(s,result);
    }
    
}

int main()
{
	char fromParent[] = "/tmp/fifo3";
    char fromFinder[] = "/tmp/fifo5";
    char toParent[] = "/tmp/fifo3";

    int fd;

    char outParent[1000];
	mkfifo(fromParent, 0666);
	fd = open(fromParent, O_RDONLY);
	read(fd, outParent, 1000);
	close(fd);

    char outFinder[1000];
	mkfifo(fromFinder, 0666);
	fd = open(fromFinder, O_RDONLY);
	read(fd, outFinder, 1000);
	close(fd);

	char* finalString;
	char stringsPassed[100][1000];

	char *token = strtok(fromFinder, ",");

    int i = 0;
    while (token != NULL)
    {
        stringsPassed[i][0] = '\0';
		strcpy(stringsPassed[i], token);
        token = strtok(NULL, ",");
		i++;
    }

	finalString = replaceAllWord(stringsPassed, outParent, i);

    mkfifo(toParent, 0666);
    fd = open(toParent, O_WRONLY);
    write(fd, finalString, strlen(finalString) + 1);
    close(fd);
    
    return 0;
}

