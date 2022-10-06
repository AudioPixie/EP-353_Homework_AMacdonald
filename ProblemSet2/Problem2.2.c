#include <stdio.h>

int main() {

    char note = 'A'; //change me to test
    int pitchClass;

    switch(note) { // translating from note name to pitch class

        case 'C': //checks against note 
        pitchClass = 0; //if it matches, assign this
        break; //exit the switch 

        case 'D':
        pitchClass = 2;
        break;

        case 'E':
        pitchClass = 4;
        break;

        case 'F':
        pitchClass = 5;
        break;

        case 'G':
        pitchClass = 7;
        break;

        case 'A':
        pitchClass = 9;
        break;

        case 'B':
        pitchClass = 11;
        break;

        default:
        printf("%c is not an acceptable note\n", note); return 1; //stops the program here if the note was invalid

    }

    printf("A note '%c' translates to %i in pitch class.\n", note, pitchClass); //prints results/

}