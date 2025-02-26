#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int min, max;

    printf("Welcome to my Random Number Generator game:");

    printf("welcome");
    scanf("%d", &min);

    printf("second");
    scanf("%d", &max);

    srand(time(NULL));
    int random_number = (rand() % (max - min + 1)) + min;

    printf("Random number between %d and %d: %d\n", min, max, random_number);
    return 0;
}