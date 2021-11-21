#include <stdio.h>
#include "decoder.h"
#include "string.h"
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
char *decodeText(char *message)
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
	return message;
	
}

//  int main()
//  {
//  	char message[100], ch;
// 	int i, key;
//  	printf("Enter a message to decrypt: ");
//  	gets(message);
//  	printf("%s", decodeText(message));
//  	printf("\n");
//  	return 0;
//  }
