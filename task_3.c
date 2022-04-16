#include <stdio.h>
#define CTRL_F 6

/*
 * Task: Write console input to the file
 */
int main(int argc, char *argv[])
{
    //check for arguments
    if (argc > 2)
    {
        fprintf(stderr, "Too much parameters.\n"
               "Required number  of params - 1 : DESTINATION_FILE_NAME\n");
        return 1;
    }
    else if (argc == 1)
    {
        fprintf(stderr, "Not enough parameters\n"
                        "Required number  of params - 1 : DESTINATION_FILE_NAME\n");
        return 1;
    }

    char* write_path = argv[1]; //destination file path
    FILE* f_write = NULL; //file handler
    char get_input = '0'; //where to read

    //try open file
    if ((f_write = fopen(write_path, "w")) == NULL)
    {
        fprintf(stderr, "Unable to open the file\n");
        return 1;
    }

    printf("Enter Ctrl+F then ENTER to stop:\n");
    //read till the end of file
    while (1) {
        get_input = getc(stdin);
        if (get_input == CTRL_F)
            break;
        fputc(get_input, f_write);
    }
    printf("\n");
    //try close the file
    if (fclose(f_write))
    {
        fprintf(stderr, "Error occurred during closing the file\n");
        return 1;
    }
    return 0;
}

