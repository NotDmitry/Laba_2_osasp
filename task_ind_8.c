#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ftw.h>

static unsigned int total_size = 0;
static unsigned int total_on_disk = 0;
static int sum(const char *fpath, const struct stat *sb, int typeflag){
    total_size += sb->st_size;
    total_on_disk += sb->st_blksize * sb->st_blocks;
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

    if (ftw(dir_name, sum, 200)) {
        perror("ftw");
        return 2;
    }
    printf("Size in bytes : %d\n"
           "Size in blocks: %d\n"
           "Disk space efficiency: %.2f%%\n", total_size, total_on_disk, ((float)total_size/(float)total_on_disk * 100));
    return 0;
}
