#include <stdio.h>

void setArray(int *numbers, int value, int size); // function prototype declaration

int main() {

    int userInput, numbers[8];

    printf("Enter an integer to initialize the array:");
    scanf("%i", &userInput); // gets the number to insert into the array

    setArray(numbers, userInput, 8); // calls setArray function

    printf("The 'numbers' array is now initialized to %i:\n\n    ", userInput);

    for(int i = 0; i <= 7; i++)
    {
        printf("%i ", numbers[i]); // prints out the finished array
    }

    printf("\n");

}

void setArray(int *numbers, int value, int size) {

    for(int i = 0; i < size; i++)
    {
        numbers[i] = value; // assigns the value inputted by the user to every array position in numbers
    }

}