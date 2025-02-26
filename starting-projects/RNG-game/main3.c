#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateRN() {
    srand((unsigned int) time(0));
    return rand() % 10 + 1;
}

int playGame() {
    int answer = generateRN();
    int guess;
    int numGuesses = 0;
    const int maxGuesses = 3;
    
    printf("Welcome to my RNG guessing game!");
    printf("Guess a number between 1 and 10\n");
    while (numGuesses < maxGuesses) {
        scanf("%d", &guess);
        numGuesses++;
        if (guess == answer) {
            printf("\nYou win! You guessed %d in %d guesses!\n", answer, numGuesses);
            return(1);
        } else if (guess > answer) {
            printf("Too high! the number is lower.\n");
        } else if (guess < answer) {
            printf("Too low! the number is higher\n.");
        }
    }
    printf("\nYou've lost... \nThe number was %d. \n", answer);
    return 0;

}

int AskplayAgain() {
    char response;
    printf("Would you like to play again? Enter y or n: ");
    scanf(" %c", &response);
    return response == 'y' || response == 'Y';
}

int main() {
    int playAgain = 1;

    while (playAgain) {
        playGame();
        playAgain = AskplayAgain();
    }
    return 0;
}
