#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

char *remove_white_spaces(char *str)
{
	int i = 0, j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
          str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return str;
}
void decodeText(char *message, char decocdedText[])
{
	int i;
	char ch;
	int key = 3;
	strcpy(message,remove_white_spaces(message));
	
	for (i = 0; message[i] != '\0'; ++i)
	{
		ch = message[i];
		if (ch >= 'a' && ch <= 'z')
		{
			ch = ch - key;
			if (ch < 'a')
			{
				ch = ch + 'z' - 'a' + 1;
			}
			message[i] = ch;
		}
		else if (ch >= 'A' && ch <= 'Z') 
		{
			ch = ch - key;
			if (ch < 'A')
			{
				ch = ch + 'Z' - 'A' + 1;
			}
			message[i] = ch;
		}
	}
	
	decocdedText[0] = '\0';

	strcpy(decocdedText, message);
	
}

 int main()
 {
	
 	char fromMain[] = "/tmp/fifo1";
	char toFinder[] = "/tmp/fifo4";
	int fd1;
	char outMain[1000];
	char decodedText[1000];

	mkfifo(fromMain, 0666);
	fd1 = open(fromMain, O_RDONLY);
	read(fd1, outMain, 1000);
	close(fd1);

	decodeText(outMain, decodedText);

	int fd2;
	mkfifo(toFinder, 0666);
	fd2 = open(toFinder, O_WRONLY);
	
	write(fd2, decodedText, strlen(decodedText) + 1);
	close(fd2);
 	return 0;
 }
