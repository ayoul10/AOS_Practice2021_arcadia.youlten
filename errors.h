#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define OFFSET_FAT16 19
#define SIZE_FAT16 2
#define ELEMENTS_TO_READ_FAT16 1

int command_line_error_check(int argc, char *argv[]);


#endif