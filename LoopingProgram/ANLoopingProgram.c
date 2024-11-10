#include <stdio.h>
#include <stdlib.h>
/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
* Purpose: Simulates a jump rope challenge using four loops: do-while, while, for, and goto.
*          The user inputs a number of jumps (between 1 and 12), and the program performs the jumps using each loop.
*
* Program name: JumpRopeChallenge.c
*
* Invocation: ./JumpRopeChallenge
*
* Variables:
*   short int jumpRope;     // Number of jumps entered by the user (between 1 and 12)
*   short int jumpCount;    // Counter to track the number of completed jumps in each loop
*   short int ScanRet;      // Holds the return value of scanf to validate user input
*
* Functions called: None
*
* Written by: An Nguyen                                                         
* Date: 09/28/2024 
* 
* Modification: None
*
* Special notes: 
*   - User must input integer from 1 to 10
*   
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

int main() 
{
    short int jumpRope;
    short int jumpCount;
    short int ScanRet;

    printf("Welcome to the Jump Rope Challenge!\n");

    do 
    {
        printf("How many jumps do you want to do? Enter a positive number between 1 and 12: ");
        ScanRet = scanf("%d", &jumpRope);
        while (getchar() != '\n');  // flush the buffer
        if (ScanRet < 1)
        {
            printf("No number found, please enter a number.\n");
            jumpRope = 0;
        }
        if (jumpRope <= 0 || jumpRope > 12) 
        {
            printf("Invalid input. Please enter a positive number in the requested range.\n");
        }
    } 
    while (jumpRope <= 0 || jumpRope > 12); //ensure input within the valid range

    // Do-While loop
    jumpCount = 1;
    printf("\nDo-While Loop:\n");
    do 
    {
        printf("Do-While Loop: You completed jump %d\n", jumpCount);
        jumpCount++;
    } 
    while (jumpCount <= jumpRope);

    // While loop
    jumpCount = 1;
    printf("\nWhile Loop:\n");
    while (jumpCount <= jumpRope) 
    {
        printf("While Loop: You completed jump %d\n", jumpCount);
        jumpCount++;
    }

    // For loop
    printf("\nFor Loop:\n");
    for (jumpCount = 1; jumpCount <= jumpRope; jumpCount++) 
    {
        printf("For Loop: You completed jump %d\n", jumpCount);
    }

    // Goto loop
    jumpCount = 1;
    printf("\nGOTO Loop:\n");
JUMP_ROPE_LOOP:
    if (jumpCount <= jumpRope) 
    {
        printf("GOTO Loop: You completed jump %d\n", jumpCount);
        jumpCount++;
        goto JUMP_ROPE_LOOP;
    }

    printf("\nCongratulations! You completed %d jumps!\n", jumpRope);

    return(0);
}
