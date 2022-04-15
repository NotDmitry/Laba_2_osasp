#include <stdio.h>
#include <sys/stat.h>

/* Task: copy one file to another */
int main(int argc, char *argv[])
{
    //check for arguments
    if (argc > 3)
    {
        fprintf(stderr, "Too much parameters\n"
                        "Required number of params - 2: SOURCE_FILE, DEST_FILE\n");
        return 1;
    }
    else if (argc == 1)
    {
        fprintf(stderr, "Not enough parameters\n"
                        "Required number of params - 2: SOURCE_FILE, DEST_FILE\n");
        return 1;
    }

    char* src_path = argv[1]; //path to source file
    char* dest_path = argv[2]; //path to destination file

    //file handlers
    FILE* src_file;
    FILE* dest_file;

    char get_input = '0'; //where to read

    //try open source file
    if ((src_file = fopen(src_path, "r")) == NULL)
    {
        fprintf(stderr, "Unable to open the file");
        return 1;
    }

    //try open destination file
    if ((dest_file = fopen(dest_path, "w")) == NULL)
    {
        fprintf(stderr,"Unable to open the file");
        return 1;
    }

    //Copy privileges from source to destination file using stat struct
    struct stat buff;
    if (stat(src_path, &buff))
    {
        fprintf(stderr, "Unable to copy the mode");
    }
    else
        chmod(dest_path, buff.st_mode);

    //copy content of file
    while ( (get_input = fgetc(src_file)) != EOF)
    {
        fputc(get_input, dest_file);
    }

    //try close two files
    if (fclose(src_file))
    {
        fprintf(stderr, "Error occurred during closing the file\n");
        return 1;
    }
    if (fclose(dest_file))
    {
        fprintf(stderr, "Error occurred during closing the file\n");
        return 1;
    }
    return 0;
}

