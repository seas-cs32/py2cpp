#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RESPONSE_MAXLEN 10

int input(char *);

int main(void) {
    int a_number;
    a_number = input("Please type a number: ");
    printf("You typed %d\n", a_number);
    return 0;
}

int input(char *prompt) {
    /* Grabs a number from the user. The number should be
     * no more than 9 characters in length. */

    char response[RESPONSE_MAXLEN];
    int i = 0;           /* index into string response */
    int result = 0;      /* int result we'll return */
    bool is_neg = false; /* true if result is negative */

    /* Grab the user's response */
    printf("%s", prompt);
    fgets(response, RESPONSE_MAXLEN, stdin);

    /* Check for a sign character */
    if (response[0] == '+' || response[0] == '-') {
        if (response[0] == '-') is_neg = true;
        i += 1;
    }

    /* Convert the response string into an integer */
    while (response[i] != '\n' && i != RESPONSE_MAXLEN) {
        /* Check for bad input */
        if (response[i] < '0' || response[i] > '9') {
            printf("ERROR: Response wasn't a number\n");
            exit(1);
        }

        /* Update running result */
        result = (result * 10) + (response[i] - '0');

        i++;
    }

    /* Check for response of a valid length */
    if (response[i] != '\n') {
        printf("ERROR: Response must be fewer than %d digits\n",
               RESPONSE_MAXLEN);
        exit(1);
    }

    /* Deal with sign character, if one was typed */
    if (is_neg) {
        result *= -1;
    }
    
    return result;
}