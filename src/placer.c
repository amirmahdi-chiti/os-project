
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
void replaceAllWord(char newWord[][1000],const char* s, int size, char output[]){
	char strOut[1000];
	strOut[0] = '\0';
	strcpy(strOut, s);
    for (int i = 0; i < size; i++)
    {
        char* n = newWord[i];
        //char* result = NULL;
		char* got = replaceWord(strOut,n);
		// printf("%s\n", got);
		strcpy(strOut, got);
        //printf("Result: %s\n", result);
        //strcpy(s,result);
    }
    // printf("%s", strOut);
	strcpy(output, strOut);
}

void writeInFile(char * filename , char* s)
{
    
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return;
    }
    
    fprintf(fp, "%s",s);

    fclose(fp);
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

	char finalString[1000];
	char stringsPassed[100][1000];
	// printf("%s\n", outParent);

	char *token = strtok(outFinder, ",");

    int i = 0;
    while (token != NULL)
    {
        stringsPassed[i][0] = '\0';
		strcpy(stringsPassed[i], token);
        token = strtok(NULL, ",");
		i++;
    }
	
	replaceAllWord(stringsPassed, outParent, i, finalString);
	writeInFile("placed.txt", finalString);

    mkfifo(toParent, 0666);
    fd = open(toParent, O_WRONLY);
    write(fd, finalString, strlen(finalString) + 1);
    close(fd);
    return 0;
}

