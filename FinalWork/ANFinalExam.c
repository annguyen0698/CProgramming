#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h> 

#define MAXWORDS 50
#define WORD_LENGTH 20      //Constant for the word buffer size

/***************************************************************************************************************
*  
*  Purpose: This program reads a list of reserved words from input_file_1, sorts them alphabetically, 
* parses input_file_2 word by word, converting each word to lowercase. It performs a binary search to check 
* if the word is in the reserved list. If the word isn't found, it is printed;
* otherwise, the program moves to the next word, allowing for multiple occurrences.
*  
*  Program Name: ANFinalExam.c
*  
*  Invocation: ./ANFinalExam
*  
*  Variables:
* Variables:
*   short int Re:                               Return code for program execution status.
*   char words[MAXWORDS][LENGTH]                Array to store words read from input file.
*   short int count:                            Total number of words read from input file.
*   short int scan_result:                      Stores the result of fscanf().
*   short int sl_index:                         Index for iterating over sorted array of words.
*   short int current_index:                    Index used to compare and swap adjacent elements.
*   short int outerloop_index:                  Index for outer loop.
*   bool swapped:                               Flag to track if a swap occurred during sorting. If none, break the loop.
*   int holder:                                 Temporary variable use for swapping value
*  
*   char Find[WORD_LENGTH]:                     Buffer characters of 1 word
*   int character_count:                        Counter for the number of characters in the current word.
*   bool found_word:                            Flag if a word is being processed.
*   char byte:                                  Stores current character being read from input file.
*
*   short int start_index, end_index:           Binary search range uses in loop for fiding the target word.
*   int middle_index:                           Middle index for the binary search.
*   short int compare_resultm, compare_results, compare_resulte: Stores the comparison results between the target and the middle, start, and end word.
*
*  Functions:
*      - FlushArray(char Find[]):                    Clears the word buffer
*  
*  Written by: An Nguyen
*  Date: 10/17/2024
*  
*  Special Notes: 
*  None
 *********************************************************************************************************/

void FlushArray(char Find[]) 
{
    short int Lcount;
    for (Lcount= 0; Lcount < WORD_LENGTH; Lcount++) 
    {
        Find[Lcount] = '\0';  
    }
}

int main()
{   
    // SET UP FOR READ THE RESERVEDWORD LIST AND PRINT OUT THE SORTED LIST 
    short int Re = 0; 
    short int scan_result;
    short int count = 0;
    char words[MAXWORDS][WORD_LENGTH];
    short int outerloop_index;
    short int current_index;
    bool swapped;
    short int sl_index;
    char holder[WORD_LENGTH];
    //SET UP TO READ FINAL EXAM TO PARSE 
    char Find[WORD_LENGTH];  
    short int character_count = 0; 
    bool found_word = false; 
    char byte;              
    //SET UP FOR BINARY SEARCH
    short int start_index, end_index, middle_index;
    short int compare_resultm, compare_results, compare_resulte;

    // Open input file for reading
    FILE *input_file_1;
    FILE *input_file_2;
    
    input_file_1 = fopen("FinalReservedWords.txt", "r");
    if(input_file_1 == NULL)
    {
        printf("Input file FinalReservedWords.txt failed to open!\n");
        Re = 1;
        goto EOP;
    }
    
    input_file_2 = fopen("FinalExamTextToParse.txt", "r");
    if (input_file_2 == NULL)
    {
        printf("Input file FinalExamTextToParse.txt failed to open!\n");
        Re = 2;
        goto EOP;
    }

    // Read from file and count the total of words:
    do
    {
        scan_result = fscanf(input_file_1, "%s", words[count]);
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

    // Start outer loop for sorting the words using bubble sort
    for(outerloop_index = 0; outerloop_index < count - 1; outerloop_index++)
    {
        swapped = false;

        // Start inner loop
        for(current_index = 0; current_index < (count - outerloop_index  -1); current_index++)
        {
            if (strcmp(words[current_index], words[current_index + 1]) > 0)  // Compare 2 adjacent words 
            {
                strcpy(holder, words[current_index]);
                strcpy(words[current_index], words[current_index + 1]);
                strcpy(words[current_index + 1], holder);
                swapped = true;
            }              
        }

        if (swapped == false) // If no swap occurred, list is sorted
        {
            break;
        }
    }   // End of outer loop 

    fclose(input_file_1);   

    // Print the sorted list of words
    printf("\nList of sorted words:\n");
    for (sl_index = 0; sl_index < count; sl_index++)
    {
        printf("%s\n", words[sl_index]);
    }
    printf("\n\n ***** \n\n");
    printf("Words Not On The List\n\n");
    

    do
    {
        byte = fgetc(input_file_2);
        if (byte == '-' || byte == '\'')
        {
            continue;
        }
        
            if (isalpha(byte))      
            {
                byte = tolower(byte);
                found_word = true;
                Find[character_count] = byte;  // Add the character to the word buffer
                character_count++;
            }                       // End of if
            else if (found_word == true)
            {
                Find[character_count] = '\0';

                // Initialize binary search variables
                start_index = 0;
                end_index = count - 1;

                // Perform Binary Search
                while (start_index <= end_index) 
                {
                    middle_index = (start_index + end_index) / 2;  // Get the middle index
                    compare_resultm = strcmp(Find, words[middle_index]); // Compare Find with middle_index
                    compare_results = strcmp(Find, words[start_index]);  // Compare Find with start_index
                    compare_resulte = strcmp(Find, words[end_index]);    // Compare Find with end_index
                    // Check if the word matches any of the indices
                    if (compare_resultm == 0 || compare_results == 0 || compare_resulte == 0) 
                    {
                        break;  
                    }
                    else if (compare_resultm < 0) // Find is smaller
                    {
                        end_index = middle_index - 1;  
                    } 
                    else // Find is larger
                    {
                        start_index = middle_index + 1;
                    }  // End of if loop
                }  // End of while loop

                // If the word was not found on the reserved word, then we print it out. 
                if (start_index > end_index) 
                {
                    printf("%s\n ", Find);
                }
                FlushArray(Find);
                found_word = false;
                character_count = 0;
            }                       // End of else if
                                  
    }                               // end of do
    while (byte != EOF);  

        if (found_word == 1)
        {
            Find[character_count] = '\0'; 

            // Initialize binary search variables
            start_index = 0;
            end_index = count - 1;

            // Perform Binary Search
            while (start_index <= end_index) 
            {
                middle_index = (start_index + end_index) / 2;  // Get the middle index
                compare_resultm = strcmp(Find, words[middle_index]); // Compare Find with middle_index
                compare_results = strcmp(Find, words[start_index]);  // Compare Find with start_index
                compare_resulte = strcmp(Find, words[end_index]);    // Compare Find with end_index

                // Check if the word matches any of the indices
                if (compare_resultm == 0 || compare_results == 0 || compare_resulte == 0) 
                {
                    break;  // Exit the loop after finding the word
                }
                else if (compare_resultm < 0) // Find is smaller
                {
                    end_index = middle_index - 1;  
                } 
                else // Find is larger
                {
                    start_index = middle_index + 1;
                }  // End of if loop
            }  // End of while loop

            // If the word was not found
            if (start_index > end_index) 
            {
                printf("%s\n", Find);
            }

            FlushArray(Find);  // Clear the buffer
            found_word = false;
            character_count = 0;
        }
    

    fclose(input_file_2);  // Close the second file
    printf("\n\n");

EOP:
    return (Re);
}
