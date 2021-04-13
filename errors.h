#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define OFFSET_FAT16 19
#define SIZE_FAT16 2
#define ELEMENTS_TO_READ_FAT16 1
#define FAT16_FILETYPE 0

#define OFFSET_EXT2 1080
#define SIZE_EXT2 2
#define ELEMENTS_TO_READ_EXT2 1
#define EXT2_FILETYPE 0xEF53

int command_line_error_check(int argc, char *argv[]);

#endif