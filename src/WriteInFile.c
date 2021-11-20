#include <stdio.h>

void writeInFile(char * filename , char* s)
{
    

    // open the file for writing
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return -1;
    }
    // write to the text file
    
    fprintf(fp, "%s",s);

    // close the file
    fclose(fp);

    
}
int main(){

    writeInFile("test.txt","salam");
    return 0;
}