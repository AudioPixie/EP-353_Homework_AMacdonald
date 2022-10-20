#include <stdio.h>

void beatbox(int bar); //function prototype declaration

int main() {

    int userInput;

    printf("How many bars would you like to beatbox?");
    scanf("%i", &userInput); // gets user input

    beatbox(userInput); // runs beatbox with the user input

}

void beatbox(int bar) {

    for(int i = 1; i <= bar; i++) // loops as any times as user input
    {
        if(i % 4 == 0){
            printf("Potato Cats!\n\n"); // prints if the line number is a multiple of 4
        }

        else {
            printf("Boots N Cats N\n"); // prints for every other line
        }
    }
}