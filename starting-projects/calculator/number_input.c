#include <stdio.h>

int main() {
    double num1, num2;
    char operator; 

    printf("\nWelcome to my calculator. \n");


    printf("Enter operator (+, -, *. /)\n ");
    scanf(" %c", &operator);

    printf("Enter your first number \n");
    scanf(" %lf", &num1);

    printf("Enter your second number \n");
    scanf(" %lf", &num2);

    if (operator == '+') {
        printf("Result: %.2f\n", num1 + num2); 
    } else if (operator == '-') {
        printf("Result: %.2f\n", num1 - num2);
    } else if (operator == '*') {
        printf("Result: %.2f\n", num1 * num2); 
    } else if (operator == '/') {
        if (num2 != 0) {
            printf("Result: %.2f/n", num1 / num2);
        } else {
            printf("Error: Divison by zero \n");
        }
    } else {
        printf("Invalid operator\n");
    }

    return 0;
}
