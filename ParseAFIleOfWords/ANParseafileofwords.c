#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define WORD_LENGTH 20    
/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
* Purpose: This program will read in a text file, and parse (separate) out
* each of the words in the file and print each of the words on their own line.
* Program name: ANParseafileofwords.c
*
* Invocation: ./ANParseafileofwords
*
* Variables:
*   short int Re:                               Return code for program execution status.
*   char Find[WORD_LENGTH]:                     Buffer characters of 1 word
*   int character_count:                        Counter for the number of characters in the current word.
*   bool found_word:                            Flag if a word is being processed.
*   char byte:                                  Stores current character being read from input file.
*
* Functions called:
*   FlushArray(char Find[]):                    Clears the word buffer 
*   
* Written by: An Nguyen                                                      
* Date:       10/17/2024
* 
* Modification: None
*
* Special notes: This program prints the words found in the input file, ignores hyphens and apostrophes.
*   
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

// Function to flush the buffer
void FlushArray(char Find[]) 
{
    int Lcount;
    for (Lcount = 0; Lcount < WORD_LENGTH; Lcount++)
    {
        Find[Lcount] = '\0';  
    }
}

int main()
{
    char Find[WORD_LENGTH];  
    int character_count;     
    bool found_word = false;        
    char byte;             
    short int Re;
    character_count = 0; 
    Re = 0; 
    FILE *infile;
    // Open input file
    infile = fopen("FinalExamTextToParse.txt", "r");
    if (infile == NULL) 
    {
        printf("Input file FinalExamTextToParse.txt failed to open!\n");
        Re = 1;
        goto EOP;
    }

    do
    {
        byte = fgetc(infile);
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
            printf("Word found: %s\n", Find);
            FlushArray(Find);
            found_word = false;
            character_count = 0;
        }                       // End of else if
                                  
    }                               // end of do
    while (byte != EOF);
/*
        // reach the end of the file
        if (found_word == true) 
        {
            Find[character_count] = '\0';  
            printf("Word found: %s\n", Find);  
            FlushArray(Find);  // Flush the buffer
            found_word = 0;  // Reset word flag
            character_count = 0;  // Reset character count
        }           // End of if found word
    
*/
    // Close input file
    fclose(infile);
EOP:
    return (Re);
}
