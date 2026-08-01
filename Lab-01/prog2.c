/*
-------------------------------------------------------
Program    : Question 2
Title      : Fair vs Biased Coin Simulation
Subject    : Design and Analysis of Algorithms
Language   : C
Author     : Sarthak Kumar Rout
Institute  : IIIT Bhubaneswar
Semester   : 3rd Semester
-------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    int tosses;
    int fairHead = 0, fairTail = 0;
    int biasedHead = 0, biasedTail = 0;

    printf("Enter number of coin tosses: ");
    scanf("%d", &tosses);

    srand(time(NULL));

    // Fair Coin Simulation
    for(int i = 0; i < tosses; i++)
    {
        if(rand() % 2)
            fairHead++;
        else
            fairTail++;
    }

    // Biased Coin Simulation (70% Head)
    for(int i = 0; i < tosses; i++)
    {
        int r = rand() % 100;

        if(r < 70)
            biasedHead++;
        else
            biasedTail++;
    }

    printf("\n========== FAIR COIN ==========\n");
    printf("Heads = %d\n", fairHead);
    printf("Tails = %d\n", fairTail);
    printf("Probability of Head = %.4f\n",
           (float)fairHead / tosses);

    printf("\n========== BIASED COIN (70%% Head) ==========\n");
    printf("Heads = %d\n", biasedHead);
    printf("Tails = %d\n", biasedTail);
    printf("Probability of Head = %.4f\n",
           (float)biasedHead / tosses);

    return 0;
}

/*
---------------- End of Program ----------------
*/