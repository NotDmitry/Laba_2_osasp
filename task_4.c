#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
 * Task: Output file string by string or by blocks of strings
 */
int main(int argc, char *argv[])
{
    //check for arguments
    if (argc > 3)
    {
        fprintf(stderr, "Too much parameters\n"
               "Required number of params - 2: SOURCE_FILE_NAME, READING_BLOCK_SIZE(in the string count; 0 for string by string)\n");
        return 1;
    }
    else if (argc == 1)
    {
        fprintf(stderr, "Not enough parameters\n"
                        "Required number of params - 2: SOURCE_FILE_NAME, READING_BLOCK_SIZE(in the string count; 0 for string by string)\n");
        return 1;
    }

    char* read_path = argv[1]; //source file path
    FILE* txt_file = NULL; //file handler

    unsigned long int str_count = strtoul(argv[2], NULL, 10); //string block size
    if (str_count == ULONG_MAX)
    {
        fprintf(stderr, "Unable to convert 2nd parameter into number");
        return 1;
    }

    //try open file
    if ((txt_file = fopen(read_path, "r")) == NULL)
    {
        fprintf(stderr, "Unable to open the file");
        return 1;
    }

    char get_input = '0'; //read character

    if (str_count == 0)
    {
        while (get_input != EOF)
        {
            get_input = fgetc(txt_file);
            printf("%c", get_input);
        }
    }
    else
    {
        while (get_input != EOF)
        {
            for (int i = 0; i < str_count; i++)
            {
                while (get_input != '\n' && get_input != EOF)
                {
                    get_input = fgetc(txt_file);
                    printf("%c", get_input);
                }
            }
            getc(stdin);
        }
    }

    //try close the file
    if (fclose(txt_file))
    {
        fprintf(stderr, "Error occurred during closing the file\n");
        return 1;
    }
    return 0;
}