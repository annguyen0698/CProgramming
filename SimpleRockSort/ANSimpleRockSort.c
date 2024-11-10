#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#define MAX_NUMBERS 50 // Maximum number of numbers read from file

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
* Purpose: This program reads a list of numbers from input file,  
*          prints the unsorted list and then prints the sorted list(ascending) to the terminal.
*
* Program name: ANSimpleRockSort.c
*
* Invocation: ./ANSimpleRockSort
*
* Variables:
*   int Re:                Return code for program execution status.
*   int list_of_numbers[]: Array to store numbers read from input file.
*   int count:             total number of all the numbers read from input file.
*   int scan_result:       Stores the result of fscanf().
*   int unsl_index:        Index for iterating over list_of_numbers.
*   int sl_index:          Index for iterating over sorted list_of_numbers.
*   int current_index:     Index used to compare and swap adjacent elements
*   int outerloop_index:   Index for outer loop.
*   bool swapped:          Flag to track if a swap occurred during sorting.
*   int holder:            Temporary variable use for swapping value
*
* Functions called: None
*   
* Written by: An Nguyen                                                          
* Date: 09/28/2024 
* 
* Modification: None
*
* Special notes: This program reads up to a maximum of 50 numbers.
*   
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

int main()
{
    int Re = 0;                 
    int list_of_numbers[MAX_NUMBERS];               
    int count = 0;                 
    int scan_result;                       
    int unsl_index;                 //unsort list index                    
    int sl_index;                   //sorted list index
    int current_index;
    int outerloop_index;
    bool swapped; 
    int holder; 
    
    // Open the file for reading
    FILE *input_file; 
    input_file = fopen("NumbersToSort.txt", "r");
    
    if (input_file == NULL)
    {
        printf("Error: File not found!\n");
        Re = 1;
        goto EOP; 
    }

    do
    {
            scan_result = fscanf(input_file, "%d", &list_of_numbers[count]);
            if(scan_result != EOF)
            {
            count++;
            }
            else
            {
                break;
            }
    }
    while (count < MAX_NUMBERS);

    // Print the unsorted numbers
    printf("List of unsorted numbers:\n");
    for (unsl_index = 0; unsl_index < count; unsl_index++) 
    {
        printf("%d\t", list_of_numbers[unsl_index]);
    }

    //Outer Loop    
    for (outerloop_index = 0; outerloop_index < count - 1 ; outerloop_index++) 
    {
        swapped = false;
    
        // Inner Loop
        for (current_index = 0; current_index < (count - outerloop_index - 1); current_index++) 
        {
            if(list_of_numbers[current_index] > list_of_numbers[current_index + 1])
            {
                holder = list_of_numbers[current_index];
                list_of_numbers[current_index] = list_of_numbers[current_index + 1];
                list_of_numbers[current_index + 1] = holder;
                swapped = true;
            }              
        }                   //end of inner loop
        if (swapped = false)
        {
            break;
        }
    }                       //end of outer loop

    printf("\nList of sorted number: \n");
    for (sl_index = 0; sl_index < count; sl_index++)
    {
        printf("%d\n", list_of_numbers[sl_index]);
    }

    fclose(input_file);

EOP:
    return(Re);
}
