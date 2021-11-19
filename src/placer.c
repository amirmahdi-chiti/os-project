
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "placer.h"


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
char* replaceAllWord(char newWord[][10],const char* s){
    for (int i = 0; i < 3; i++)
    {
        char* n = newWord[i];
        //char* result = NULL;
        s = replaceWord(s,n);
        //printf("Result: %s\n", result);
        //strcpy(s,result);
    }
    
}

// int main()
// {
// 	char str[] = "salam $ khobi $ . $";
	
// 	char ch_arr[3][10] = {
//                          "spike",
//                          "tom",
//                          "jerry"
//                      };

// 	char* result = NULL;


// 	printf("Old string: %s\n", str);

// 	result = replaceAllWord(ch_arr,str);
// 	printf("New String: %s\n", result);

// 	free(result);
// 	return 0;
// }

