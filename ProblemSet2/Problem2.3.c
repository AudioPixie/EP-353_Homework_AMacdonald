#include <stdio.h>

int main() {

    for(int i = 0; i <= 11; i++) { //increments through 0-11

        switch(i) {

            case 0: //checks if i matches
            printf("C "); //prints if true, no line breaks
            break; //exits switch

            case 1:
            printf("Db ");
            break;

            case 2:
            printf("D ");
            break;

            case 3:
            printf("Eb ");
            break;

            case 4:
            printf("E ");
            break;

            case 5:
            printf("F ");
            break;

            case 6:
            printf("Gb ");
            break;

            case 7:
            printf("G ");
            break;

            case 8:
            printf("Ab ");
            break;

            case 9:
            printf("A ");
            break;

            case 10:
            printf("Bb ");
            break;

            case 11:
            printf("B\n"); //last one has a line break
            break;

        }
        
    }

}