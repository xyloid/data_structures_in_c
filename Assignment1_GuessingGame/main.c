#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/* Generate a random number in the range 1-10. */
int generate() {
    int rand_number = rand();
    /*
     * Because rand() is inclusive, the random number is
     * in the range [0, RAND_MAX]. Thus, the following expression
     * is used to get an approximately uniform distribution of
     * a random number in range [1, 10].
     * */
    int ret = rand_number / (RAND_MAX + 1.0) * 10.0 + 1.0;
    return ret;
}

int main() {
    /*
     * Initialize random seed, thus different psuedo random number
     * will be generated for each time.
     * */
    srand(time(0));
    int round;
    int guess;
    int number;
    // Record how many times player guessed in each round.
    int record[5] = {0, 0, 0, 0, 0};

    // Five rounds.
    for (round = 0; round < 5; round++) {

        printf("==========================\n");
        printf("CPU Says: Pick a number 1-10\n");
        printf("==========================\n");

        number = generate();
        // Prompt until the player makes a right guess.
        do {
            printf("Make a guess: ");
            scanf("%d", &guess);
            record[round]++;
            // Give correct hint.
            if (guess > number)
                printf("No guess lower!\n");
            else if (guess < number)
                printf("No guess higher!\n");
            else {
                printf("You got it!\n");
                break;
            }
        } while (guess != number);
    }

    printf("=================================================\n");
    printf("|Here are the results of your guessing abilities|\n");
    printf("=================================================\n");

    // Print the results of all 5 rounds.
    for (round = 0; round < 5; round++) {
        printf("Game %d took you %d guesses\n", round, record[round]);
    }
    return 0;
}
