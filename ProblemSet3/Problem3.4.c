#include <stdio.h>

int numChars(char *s, char c); // function prototype declaration

int main(){

    char str[50], search;

    printf("Write a sentence:");
    scanf("%[^\n]", str); // gets the sentence to analyze

    printf("Enter the character you want to count:");
    scanf(" %c", &search); // gets the character to search for - case sensitive

    int count = numChars(str, search); // assigns the return of numChars to count

    printf("The string \"%s\" has %i '%c's.\n", str, count, search); // prints results

}

int numChars(char *s, char c) {

    int x = 0; 

    for(int i = 0; i < 50; i++) // goes through each position of the array
    {
        if(*s == c){ // increments x if the current location in the array matches the search character
            x++; 
        }

      s++; // moves to the next location
    }

    return x; // final tally of matching characters

}