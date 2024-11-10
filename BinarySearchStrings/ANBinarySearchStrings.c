#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAXWORDS 50
#define LENGTH 15
/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
* Purpose: This program print out sorted list of words from an input file with a maximum of 50 words, none longer than 15 bytes,
*          and allows the user to search for a word using binary search.
*
* Program name: ANSimpleBinarySearch.c
*
* Invocation: ./ANSimpleBinarySearch
*
* Variables:
*   //SETUP FOR READ WORD AND DISPLAY ON TERMINAL
*   short int Re:                               Return code for program execution status.
*   char words[MAXWORDS][LENGTH]                Array to store words read from input file.
*   short int count:                            Total number of words read from input file.
*   short int scan_result:                      Stores the result of fscanf().
*   short int sl_index:                         Index for iterating over sorted array of words.
*   short int current_index:                    Index used to compare and swap adjacent elements.
*   short int outerloop_index:                  Index for outer loop.
*   bool swapped:                               Flag to track if a swap occurred during sorting. If none, break the loop.
*   int holder:                                 Temporary variable use for swapping value
*   // SET UP FOR BINARY SEARCH
*   int scan_word:                              Store scanf result take from user input to search for it.
*   int start_index, end_index:                 Binary search range uses in loop for fiding the target word.
*   int middle_index:                           Middle index for the binary search.
*   char target[LENGTH]:                        Word that the user is searching for.
*   int compare_resultm, compare_results, compare_resulte: Stores the comparison results between the target and the middle, start, and end word.
*   int scan_quit:                              Stores the result of scanf when the user want to quit or continue.
*   char quit_result[LENGTH]:                   Stores the user's input in CONTINUEPROGRAM
*   int quit_cmp:                               Stores the result of comparing the quit.
*
* Functions called: None
*   
* Written by: An Nguyen                                                          
* Date: 10/13/2024 
* 
* Modification: None
*
* Special notes: This program reads up to a maximum of 50 words, none longer than 15 bytes.
*   
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/
int main()
{
    int Re = 0; 
    int scan_result;
    int count = 0;
    char words[MAXWORDS][LENGTH];
    int unsl_index;
    int sl_index;
    int outerloop_index;
    int current_index;
    bool swapped;
    char holder[LENGTH];
    // set up for Binary Search
    int scan_word; 
    int start_index;
    int end_index; 
    int middle_index;
    char target[LENGTH];
    int compare_resultm, compare_results, compare_resulte;  
    int scan_quit;
    char quit_result[LENGTH];
    int quit_cmp;


    // open file and check whether the file was opened successfully
    FILE *input_file;
    input_file = fopen("WordsForMeToSearch.txt", "r");

    if(input_file == NULL)
    {
        printf("Input file failed to open!\n");
        Re = 1;
        goto EOP;
    }

    // Read from file and count the total of words:
    do
    {
        scan_result = fscanf(input_file, "%s", words[count]);
        if(scan_result != EOF)
        {
            count++;
        }
        else
        {
            break;
        }
    }
    while (count < MAXWORDS);

    // start outer loop 
    for(outerloop_index = 0; outerloop_index < count - 1; outerloop_index++)
    {
        swapped = false;

        // start inner loop
        for(current_index = 0; current_index < (count - outerloop_index  -1); current_index++)
        {
            if (strcmp(words[current_index], words[current_index + 1]) > 0)              // Compare 2 adjacent words 
            {
                strcpy(holder, words[current_index]);
                strcpy(words[current_index], words[current_index + 1]);
                strcpy(words[current_index + 1], holder);
                swapped = true;
            }              
        }  // End of inner loop
        
        if (swapped == false) // If no swap occurred, list is sorted
        {
            break;
        }
    }   // End of outer loop 

    // Print the sorted list of words
    printf("\nList of sorted words:\n");
    for (sl_index = 0; sl_index < count; sl_index++)
    {
        printf("%s\n", words[sl_index]);
    }

    fclose(input_file);

    // start Binary Search
GETAWORD:
    printf("\nWelcome to Binary Search Program!!!\n");
    printf("\nEnter a word to search: ");
    scan_word = scanf("%s", target);  
    while (getchar() != '\n');  // Flush the buffer
    if (scan_word < 1) 
    {
        printf("No word found, please enter a word!!\n");
        goto GETAWORD;  // Repeat the input if invalid
    }
BSLOOP:
    // Debug print to ensure the word was entered
    printf("You entered word: %s\n", target);

    // Binary search setup
    start_index = 0;
    end_index = count - 1;

    // Perform binary search
    while (start_index <= end_index) 
    {
        middle_index = (start_index + end_index) / 2;  // Get the middle index
        compare_resultm = strcmp(target, words[middle_index]); // Compare target with middle_index
        compare_results = strcmp(target, words[start_index]);  // Compare target with start_index
        compare_resulte = strcmp(target, words[end_index]);    // Compare target with end_index

        if (compare_resultm == 0 || compare_results == 0 || compare_resulte == 0) 
        {
            printf("Found it!!!\n");
            break;
        } 
        else if (compare_resultm < 0) // target is smaller than the middle
        {
            end_index = middle_index - 1;  
        } 
        else 
        {
            start_index = middle_index + 1;  // target is larger than the middle
        }   // end of if loop
    } // End of while loop 

    // If the word was not found
    if (start_index > end_index) 
    {
        printf("Word '%s' was not found in the list.\n", target);
    }
    
CONTINUEPROGRAM:
    // Present the list of sorted words again, and prompt the user for another word to search.
    printf("\nList of sorted words:\n");
    for (sl_index = 0; sl_index < count; sl_index++)
    {
        printf("%s\n", words[sl_index]);
    }

    // Modified the message here
    printf("\nType 'quit' to exit, or type any other word to search again: ");
    scan_quit = scanf(" %s", quit_result); 
    while (getchar() != '\n');  // Flush the input buffers
    
    if (scan_quit < 1) 
    {
        printf("\nInvalid input, please enter a valid word or 'quit' to exit!!\n");
        goto CONTINUEPROGRAM;  
    }
    
    quit_cmp = strcmp(quit_result, "quit");
    if (quit_cmp == 0) 
    {
        printf("\nEnd of this program!!!\n");
        goto EOP;
    } 
    else 
    {
        strcpy(target, quit_result);
        goto BSLOOP;  
    }

EOP:
    return(Re);
}