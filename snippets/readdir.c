// Prints the current workign directory and its contents

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

void print_cwd(const char* dir);

int main(int argc, char** argv)
{
    if (argc == 2)
    {
        print_cwd(argv[1]);
        struct dirent* entry = NULL;
        DIR* dir = opendir(argv[1]);

        if(dir == NULL)
        {
            return 1;
        }

        while((entry = readdir(dir)) != NULL)
        {
            printf("%s\n", entry->d_name);
        }
    }
}

void print_cwd(const char* dir)
{
    if(chdir(dir) != 0)
    {
        printf("%s, not found", dir);
        return;
    }

    long size = 0;
    char* buffer = NULL;
    char* ptr = NULL;

    size = pathconf(dir, _PC_PATH_MAX);

    if((buffer =(char*)malloc((size_t)size)) != NULL)
    {
        ptr = getcwd(buffer, (size_t) size);
    }

    printf("%s\n", buffer);
    
}

