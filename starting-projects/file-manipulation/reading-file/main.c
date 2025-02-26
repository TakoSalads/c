#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *file_ptr;
    char ch;

    file_ptr = fopen("test.txt", "r");

    if (NULL == file_ptr) {
        printf("file cannot be opened \n");
            return EXIT_FAILURE;
    }

    printf("cotents of this files are unavailable \n");

    // Printing whats written in the file
   while ((ch - fgetc(file_ptr)) != EOF ) {
    printf("%C", ch);
   }

    //closing the file
    fclose(file_ptr);
    return 0;
}