// A C/C++ program for splitting a string
// using strtok()
#include <stdio.h>
#include <string.h>
char** splitInput(char* s,char* deli){
    int end1=0,end2=0;
    int count = 0;
    char **strArr=(char**)malloc(sizeof(char*)*3);
    for(int i=0;i<3;i++)
    {
        strArr[i]=(char*)malloc(200);
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
    printf("end 1 = %d\n", end1);
    printf("end 2 = %d\n", end2);
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
int main()
{
	char str[] = "Geeks###for###Geeks";
    char** arr;
    char deli[] = "###";
    arr = splitInput(str,deli);
    printf("%s\n", arr[0]);
    printf("%s\n", arr[1]);
    printf("%s\n", arr[2]);

    return 0;

}

