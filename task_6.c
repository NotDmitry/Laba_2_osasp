#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

/*
 * Task: output contents of root and current directories
 */

#define ROOT "/"

int print_dir(char* dirname);

int main(int argc, char *argv[])
{
    char this[MAXNAMLEN]; //current directory
    if (getcwd(this, MAXNAMLEN) == NULL)
    {
        fprintf(stderr, "Unable to get current directory name");
        return 1;
    }
    printf("==========CURRENT==========\n");
    if(!print_dir(this))
    {
        fprintf(stderr, "Unexpected error");
        return 1;
    }
    printf("==========ROOT========\n");
    if(!print_dir(ROOT))
    {
        fprintf(stderr, "Unexpected error");
        return 1;
    }
    return 0;
}

//Print the content of one directory passed by dirname (path)
int print_dir(char* dirname)
{
    DIR *current_dir;
    //try open the directory
    if ((current_dir = opendir(dirname)) == NULL)
    {
        fprintf(stderr, "Unable to open directory");
        return 0;
    }

    //using dirent->name to get subdirectories and file names
    //if all the content is read readdir will further return NULL
    struct dirent *data;
    while ((data = readdir(current_dir)) != NULL)
    {
        printf("%s", data->d_name);
    }
    rewinddir(current_dir);

    //try close directory (0 - success)
    if (closedir(current_dir))
    {
        fprintf(stderr, "Error during closing the directory");
        return 0;
    }
    return 1; //success
}



