#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int min = 1, max = 10, guess1, i;
    
    srand(time(NULL));
    int random_number = (rand() % (max - min + 1)) + min;

    printf("\nWelcome to my Random Number Generator game");
    for (i = 0; i < 3; i++) {
        printf("\nPlease enter your guess: \n");
        scanf("%d", &guess1);
        if (guess1 == random_number) {
            printf("You win!");
            exit(0);
        } else if (guess1 >= random_number) {
            printf("Too high! the number is lower.");
        } else if (guess1 <= random_number) {
            printf("Too low! the number is higher.");
        }
        if (i = 0) {
            printf("\nGame Over");
            exit(0);
        } else {
            printf("\nNext round!\n");
        }
        
    }
}