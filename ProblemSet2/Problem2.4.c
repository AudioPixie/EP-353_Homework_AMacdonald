#include <stdio.h>

int main() {

    int number;

    printf("Enter a positive integer: "); //asking for user input
    scanf("%i", &number);

    for(int i = 1; i <= number; i+=2) { //starts at 1, counts up by 2 to the number that was entered

        printf("%i ", i); //prints the odd numbers

    }

    printf("\n"); //blank line

}