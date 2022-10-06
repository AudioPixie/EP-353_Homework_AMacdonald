#include <stdio.h>
#include <math.h>

int main()
{
    int userInput;

    //this will ask for user input, easier to test different numbers this way

    printf("Type your MIDI note number: ");
    scanf("%i", &userInput);

    char midiNote = userInput; //you can also replace userInput with the number here directly
    float frequency = pow(2, (midiNote - 69) / 12.0f) * 440; //converts midi to frequency

    if(userInput >= 0 && userInput <= 127) { //only prints if the input was 0-127
        printf("The frequency of a MIDI note number %d is %fHz.\n", midiNote, frequency); //results
    }

    else {
        printf("That is not a valid MIDI note number.\n"); //if the input wasn't 0-127
    }

}