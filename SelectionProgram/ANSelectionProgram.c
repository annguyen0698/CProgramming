#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#define BUFFER_SIZE 50      //define a constant for buffer size

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* Program name: ANSelectionProgram.c
*
* Invocation: ./ANSelectionProgram
*
* Variables:
*   char StudentScore[BUFFER_SIZE];     // holds raw input that the user provides from the terminal
*   int score_index = 0;                // index to keep track of position while processing the StudentScore array
*   char valid_score[BUFFER_SIZE];      // store only valid numeric part of user input after processing user input
*   int buffer_index = 0;               // index to keep track of position while populating valid_score array
*   int score                           // hold final parsed and validated score after input from StudentScore buffer is processed
*
* Functions called: None
*
* Written by An Nguyen                                                         *          
*           09/14/2024 
* 
* Modication: None
*
* Special notes: 
* User must input integer from 1 to 10. Non-numeric or null characters will be rejected.
*   
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

int main()
{
    char StudentScore[BUFFER_SIZE];
    int score = 0;

    GETANUMBER:
    
    printf("Please enter your grade (Note: I only accept 1 to 10) >> ");
    fgets(StudentScore, BUFFER_SIZE, stdin);
    
    int score_index = 0;
    
    //accept int, str if they have spaces around character
    while (isspace(StudentScore[score_index]))
    {
        score_index++;
    }

    // check whitespace and empty input
    if (StudentScore[score_index] == '\0'  || StudentScore[score_index] =='\n')
    {
        printf("Your input is invalid. Please try again!\n");
        goto GETANUMBER;
    }

    // store input which is not whitespace
    char valid_score[BUFFER_SIZE];
    int buffer_index = 0;

    //check negative number
    if (StudentScore[score_index] == '-')
    {
        valid_score[buffer_index] = '-';
        buffer_index++;
        score_index++;
    }

    //check the valid input(digit) next to negative sign
    if (!isdigit(StudentScore[score_index]))
    {
        printf("Your score must be an integer between 1 to 10. Please try again!\n");
        goto GETANUMBER;
    }

    // put digit into valid_score
    while(isdigit(StudentScore[score_index]))
    {
        valid_score[buffer_index] = StudentScore[score_index];
        score_index++;
        buffer_index++;
    }

    // null terminate valid_score
    valid_score[buffer_index] = '\0';

    //skip any trailing whitespace
    while(isspace(StudentScore[score_index]))
    {
        score_index++;
    }

    // anything after number accept newline or null terminator is invalid
    if (StudentScore[score_index] != '\n' && StudentScore[score_index] != '\0')
    {
        printf("You entered an invalid score. Please try again!\n");
        goto GETANUMBER;
    }

    //convert valid_score into integer
    score = atoi(valid_score);

    // only take number from 1 to 10
    if (score < 1 || score > 10)
    {
        printf("Your grade must be between 1 and 10. \n");
        goto GETANUMBER;
    }

    printf("Your student score is: %d\n", score);

    //Use ternary operator for multiple conditions: 
    printf("Your grade evaluation after using ternary operator for multiple conditions is: %s\n",
        (score == 10 || score == 9) ? "GRADE A" :
        (score == 8) ? "GRADE B" :
        (score == 7) ? "GRADE C" :
        (score >= 5) ? "GRADE D" :
        (score >= 2) ? "GRADE F" :
        "Fail the test!"
    );    

    //Grading evaluation based on if_else structure
    printf("Your grade evaluation after using if-else structure is: ");
    if (score == 10 || score == 9)
    {
        printf("GRADE A\n");   
    }
    else if (score == 8)
    {
        printf("GRADE B\n");
    }
    else if (score == 7)
    {
        printf("GRADE C\n");
    }
    else if (score >= 5)
    {
        printf("GRADE D\n");
    }
    else if (score >= 2)
    {
        printf("GRADE F\n");
    }
    else
    {
        printf("Fail the test!\n");
    }  

    //Grading evaluation by using switch: 
    printf("Your grade evaluation after using switch is: ");

    switch (score) 
    {
        case 10:
        case 9:
            printf("GRADE A\n");
            break;
        case 8:
            printf("GRADE B\n");
            break;
        case 7:
            printf("GRADE C\n");
            break;
        case 6:
        case 5:
            printf("GRADE D\n");
            break;
        case 4:
        case 3:
        case 2:
            printf("GRADE F\n");
            break;
        default:
            printf("Fail the test!\n");
            break;
    }
    
    return(0);
}
