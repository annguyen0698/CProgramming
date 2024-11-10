
#include <stdio.h>

/*
*****************************************************************************************************
* Purpose:  reads personal information (first name, last name, course name, and program name) 
* from an input file and writes that information to an output file.
* Program name: ANTestIOProgram.c   
* Invocation: ./AnFIleIOTest
*
* Variables:
*   char first_name[50];        //store first name in File IO test (1st line)
*   char last_name[50];         //store last name in File IO test (1st line)
*   char course_name[100];      //store course name in File IO test (2nd line)
*   char program_name[100];     //store program name in File IO test (3rd line)
*
*   Functions called: No custome functions
* 
* Special notes: None
*****************************************************************************************************
*/
 
int main()
{
    char first_name[10];
    char last_name[10];
    char course_name[50];
    char program_name[50];

    FILE *outfile;
    FILE *infile;

    //Variable to store return code (success or fail)
    int Re = 0;

    //open 2 files
    infile = fopen("FileIOTest.txt", "r");
    if(infile == NULL)
    {
        printf("Input file failed to open! \n");
        Re = 1;
        goto EOP;
    }

    outfile = fopen("OutputFile.txt", "w");
    if(outfile == NULL)
    {
        printf("Output file failed to open!!\n");
        Re = 2;
        goto EOP;
    }

    fscanf(infile, "%s %s", first_name, last_name); 
    printf("Name: %s %s\n", first_name, last_name);
    
    while (fgetc(infile) != '\n');
    //while(getchar()!='\n');

    fgets(course_name, 50, infile); // read the whole 2nd line
    printf("Course Name: %s", course_name);

    fgets(program_name, 50, infile); // read the whole 2nd line
    printf("Program Name: %s", program_name);

    // write the information into output file
    fprintf(outfile, "Name: %s %s\n", first_name, last_name);
    fprintf(outfile, "Course Name: %s", course_name);
    fprintf(outfile, "Program Name: %s\n", program_name);

    fclose(infile);
    fclose(outfile);


EOP: 
    if (Re == 2) 
    {
        fclose(infile);
    } 

    return (Re);
}
