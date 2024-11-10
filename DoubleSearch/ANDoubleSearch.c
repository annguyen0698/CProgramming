
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MAXWORDS 50
#define LENGTH 15
/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
* Purpose: This program print out sorted list of words from an input file with a maximum of 50 words, none longer than 15 bytes,
*          and allows the user to search for a word using binary search and sequential search. It also measures time and hơw many 
*           comparitions it takes to get the result.
*
* Program name: ANSearchComparisonProgram.c
*
* Invocation: ./ANSearchComparisonProgram
*
* Variables:
*   //SETUP FOR READ WORD AND DISPLAY ON TERMINAL
*   short int Re:                             Return code for program execution status.
*   char words[MAXWORDS][LENGTH]              Array to store words read from input file.
*   short int count:                          Total number of words read from input file.
*   short int scan_result:                    Stores the result of fscanf().
*   short int sl_index:                       Index for iterating over sorted array of words.
*   short int current_index:                  Index used to compare and swap adjacent elements.
*   short int outerloop_index:                Index for outer loop.
*   bool swapped:                             Flag to track if a swap occurred during sorting. If none, break the loop.
*   short int holder:                         Temporary variable use for swapping value
*   //SET UP FOR TIMING
*   short int compares:                        Number of comparisons in binary and sequential searches.
*   clock_t bs_start_time:                     Binary Search start of time.
*   clock_t bs_end_time:                       Binary Search end of time.
*   clock_t ss_start_time:                     Sequential search start of time.
*   clock_t ss_end_time:                       Sequential search end of time.
*   double ss_total_time:                      Total time for finding word in the sequential search (microseconds).
*   double bs_total_time:                      Total time for finding word in the binary search in (microseconds).
*   //SET UP FOR SEQUENTIAL SEARCH
*   bool index_found:                          Flag to check if the word is found in sequential search
*   short int sequential_index:                Index used in sequential search to loop through the sorted list.
*   short int ssindex_compare:                 Store the result of str cmp between target and word[index]
*   short int ss_position:                     Stores the position where the word is found 
*   //SET UP FOR BINARY SEARCH
*   short int start_index, end_index:          Start and end index from the sorted list used in binary search 
*   short int middle_index:                    used in binary search to find the middle index between end and start
*   short int compare_resultm,                 Result of comparing target and middle index.
*   short int compare_results,                 Result of comparing target and start index.
*   short int compare_resulte:                 Result of comparing target and end index.
*   short int bs_position:                     Position where the word is found in binary search.
*   //SET UP FOR CONTINUE PROGRAM
*   short int scan_quit:                       Result of scanf in continue program.
*   char quit_result[LENGTH]:                  User's input in the CONTINUEPROGRAM loop.
*   short int quit_cmp:                        The result of comparing the user's input with the string "quit".
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
    //SET UP FOR READ FILE AND SORTED LIST 
    short int Re = 0; 
    short int scan_result;
    short int count = 0;
    char words[MAXWORDS][LENGTH];
    short int sl_index;
    short int outerloop_index;
    short int current_index;
    bool swapped;
    char holder[LENGTH];

    //SET UP FOR TIME OF COMPARISION WILL BE USED IN 2 SEARCH 
    short int compares;
    clock_t bs_start_time;
    clock_t bs_end_time;
    clock_t ss_start_time;
    clock_t ss_end_time;
    double ss_total_time;
    double bs_total_time;

    // SET UP FOR SEQUENTIAL SEARCH
    bool index_found = false;       //flag to see if the word is found
    short int sequential_index;
    short int ssindex_compare; 
    short int ss_position;

    // SET UP FOR BINARY SEARCH 
    short int start_index;
    short int end_index; 
    short int middle_index;
    short int compare_resultm, compare_results, compare_resulte;
    short int bs_position;
    
    // SET UP FOR CONTINUE PROGRAM
    short int scan_quit;
    char quit_result[LENGTH];
    short int quit_cmp;


    // open file and check whether the file was opened sucessfully
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

    //SET UP TO GET A NUMBER 
    int scan_word; 
    char target[LENGTH];

GETAWORD:
    printf("\nWelcome to Searching Program!!!\n");
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

//----------------------------------BINARY SEARCH----------------------------------------


    printf("---------------------------------------------------------------------------------\n");

    printf("BINARY SEARCH\n");

    start_index = 0;
    end_index = count - 1;
    compares = 0;

    // START COUNTING TIME FOR BINARY SEARCH
    bs_start_time = clock();

    // PERFORM BINARY SEARCH 
    while (start_index <= end_index) 
    {   
        middle_index = (start_index + end_index) / 2;  // Get the middle index
        compare_resultm = strcmp(target, words[middle_index]); // Compare target with middle_index
        compare_results = strcmp(target, words[start_index]);  // Compare target with start_index
        compare_resulte = strcmp(target, words[end_index]);    // Compare target with end_index
        compares++;

        // Check if the word matches any of the indices
        if (compare_resultm == 0 || compare_results == 0 || compare_resulte == 0) 
        {
            printf("Found it!!!\n");

            // position 
            if (compare_resultm == 0) 
            {
                bs_position = middle_index + 1;
            } 
            else if (compare_results == 0) 
            {
                bs_position = start_index + 1;
            } 
            else if (compare_resulte == 0) 
            {
                bs_position = end_index + 1;
            }       // end of position loop
            printf("Binary Search: Word '%s' found at position %d.\n", target, bs_position);
 
            break;  // Exit the loop after finding the word
        }
        else if (compare_resultm < 0) // target is smaller
        {
            end_index = middle_index - 1;  
        } 
        else // target is larger
        {
            start_index = middle_index + 1;
        }       // end of if loop
    }   // end of while loop
  
    // If the word was not found
    if (start_index > end_index) 
    {
        printf("Binary Search: Word '%s' was not found in the list.\n", target);
    }

    // END OF TIME FOR FINDING A WORD 
    bs_end_time = clock();
    printf("Start time: %ld, End time: %ld\n", bs_start_time, bs_end_time);

    bs_total_time = ((double)(bs_end_time - bs_start_time)) / CLOCKS_PER_SEC * 1000000;

    printf("Binary Search took %d comparisons and %.10f microseconds to get this result.\n", compares, bs_total_time);

    //----------------------------------SEQUENTIAL SEARCH----------------------------------------

    printf("---------------------------------------------------------------------------------\n");
    printf("SEQUENTIAL SEARCH\n");

    // PERFORM SEQUENTIAL SEARCH
    compares = 0;
    index_found = false;

    // START COUNTING TIME FOR SEQUENTIAL SEARCH
    ss_start_time = clock();
    for (sequential_index = 0; sequential_index < count; sequential_index++) 
    {
        compares++;
        ssindex_compare = strcmp(words[sequential_index], target);

        if (ssindex_compare > 0) 
        {
            break; // break the loop since target is smaller and the list is
        }

        if (ssindex_compare == 0) 
        {
            // Word found
            index_found = true; // flag found
            ss_position = sequential_index + 1;  // Store 1-based index position
            break;
        }
    }
    if (index_found == true) 
    {
        printf("Found it!!!\n");
        printf("Sequential Search: Word '%s' found at position %d.\n", target, ss_position);
    } 
    else 
    {
        printf("Sequential Search: Word '%s' not found.\n", target);
    }
    // END OF TIME FOR FINDING A WORD 
    ss_end_time = clock();
    printf("Start time: %ld, End time: %ld\n", ss_start_time, ss_end_time);

    // CALCULATE TIME
    ss_total_time = ((double) (ss_end_time - ss_start_time)) / CLOCKS_PER_SEC * 1000000;

    printf("Sequential search took %d comparisons and %.10f microseconds (machine cycles) to get this result.\n", compares, ss_total_time);

    printf("---------------------------------------------------------------------------------\n");

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
