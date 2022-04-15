#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ftw.h>

static unsigned int total_size = 0;
static int sum(const char *fpath, const struct stat *sb, int typeflag){
    total_size += sb->st_size;
    return 0;
}

int main(int argc, char *argv[])
{
    //check for arguments
    if (argc > 2)
    {
        fprintf(stderr, "Too much parameters.\n"
                        "Required number  of params - 1 : DIRECTORY_PATH\n");
        return 1;
    }
    else if (argc == 1)
    {
        fprintf(stderr, "Not enough parameters\n"
                        "Required number  of params - 1 : DIRECTORY_PATH\n");
        return 1;
    }

    char* dir_name = argv[1]; //searching directory path
/*    DIR* dir_ptr;
    struct stat data;*/

    if (ftw(dir_name, sum, 20)) {
        perror("ftw");
        return 2;
    }
    printf("%d", total_size);
    return 0;
}