#include <stdio.h>

int main(){

    int numbers[7] = {5, 9, 1, 2, 4, 8, 3}; // initialize array

    for(int first = 0, last = 6; first < last; first++, last--) // starts at the extremeties of the array and moves inwards
    {
        int placeholder = numbers[first]; // copies the value in the lowest position to a placeholder
        numbers[first] = numbers[last]; // changes the lowest position to the value of the highest position
        numbers[last] = placeholder; // changes the highest position to the saved lowest value
    }

    for(int i = 0; i <= 6; i++)
    {
        printf("The value of arr at index %i is %i\n", i, numbers[i]); // prints the reordered array
    }
}