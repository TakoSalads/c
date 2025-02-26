#include <stdio.h>

int main() {
    char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    char *deck[52];
    int index = 0;

    for (int s = 0; s < 4; s++) {
        for (int r = 0;  r < 13; r++) {
            static char card[20];
            snprintf(card, sizeof(card), "%s of %s", ranks[r], suits[s]);
        }
    }

    //print the deck
    for (int i = 0; i < 52; i++) {
        printf("%s\n", deck[i]);
    }

    return 0;
}