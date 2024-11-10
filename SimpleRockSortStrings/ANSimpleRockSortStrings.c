#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAXWORDS 50
#define LENGTH 15
/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
* Purpose: This program reads a list of words from input file with maximum 50 words, none longer than 15 bytes, 
*          prints the unsorted list and then prints the sorted list(ascending) to the terminal.
*
* Program name: ANSimpleRockSortStrings.c
*
* Invocation: ./ANSimpleRockSortStrings
*
* Variables:
*   int Re:                             Return code for program execution status.
*   char words[MAXWORDS][LENGTH]       Array to store words read from input file.
*   int count:                          Total number of words read from input file.
*   int scan_result:                    Stores the result of fscanf().
*   int unsl_index:                     Index for iterating over array of words.
*   int sl_index:                       Index for iterating over sorted array of words.
*   int current_index:                  Index used to compare and swap adjacent elements.
*   int outerloop_index:                Index for outer loop.
*   bool swapped:                       Flag to track if a swap occurred during sorting. If none, break the loop.
*   int holder:                         Temporary variable use for swapping value
*
* Functions called: None
*   
* Written by: An Nguyen                                                          
* Date: 10/05/2024 
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

    // open file and check whether the file was opened sucessfully
    FILE *input_file;
    input_file = fopen("WordsToSort.txt", "r");

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

    //print unsorted word list to terminal:
    printf("Unsorted word list: ");
    for (unsl_index = 0; unsl_index < count; unsl_index++)
    {
        printf("%s\t",words[unsl_index]);
    }

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
EOP:
    return(Re);
}