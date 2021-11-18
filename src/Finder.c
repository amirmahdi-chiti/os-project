#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// "Finder" is used to store bounds and the string which is found
// from the bounds.
struct Finder
{
    int start;
    int end;
    char str[500];
};

void findSubStr(char[], int, int, char[]);

int main(/*char** received*/) {
    // "received[0]" is the the bounds string which is the string we
    // want to decode the bounds from.
    char boundsString[10000] = "1 2$5 6$7 11$";/*received[0];*/
    char proccessString[10000] = "Hello this is Majid Dareini from Sabzevar";/*received[1];*/
    
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
            int endNumber = atoi(number);
            finders[boundCnt].end = endNumber;
            // In the next line we empty the number string 
            memset(number, 0, strlen(number));
            char str[10000] = "";
            // In the next function we find the substring and that will be stored in str
            findSubStr(proccessString, finders[boundCnt].start, endNumber, str);
            int k;
            // In the following code we copy str to the finder's str
            for (k = 0; str[k] != '\0'; k++)
                finders[boundCnt].str[k] = str[k];
            finders[boundCnt].str[k] = '\0';
            boundCnt++;
        }
    }

    // This is just an example output to see that the code works correct
    // and after being sure it will be changed.
    for (int i = 0; i < boundCnt; i++) {
        printf("the string is:\"%s\" and begins from %d and ends in %d.\n"
        , finders[i].str, finders[i].start, finders[i].end);
    }
    
    return 0;

}

// In the next function we find the substring and that will be stored in str
void findSubStr(char str[], int s, int e, char result[]) {
    for (int i = s; i <= e && str[i] != '\0'; i++)
    strncat(result, &str[i], 1);
}