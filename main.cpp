#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("\nError! please pass an operation (probably /find) and a disk volume of EXT2 or FAT16");
    }
    else if (argc > 2)
    {
        printf("\nError! Too many arguments! please pass an operation (probably /find) and a disk volume of EXT2 or FAT16");
    }
    else
    {

        printf("\n We're inside the program");
        
    }

    return 0;
}
