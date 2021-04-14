#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include "Fat16.h"
//#include "Ext2.h"
//#include "Disk.h"

using namespace std;

#define OFFSET_FAT16 19
#define SIZE_FAT16 2
#define ELEMENTS_TO_READ_FAT16 1
#define FAT16_FILETYPE 0

#define OFFSET_EXT2 1080
#define SIZE_EXT2 2
#define ELEMENTS_TO_READ_EXT2 1
#define EXT2_FILETYPE 0xEF53

#define UNKNOWN -1
#define FAT16 0
#define EXT2 1

int fileTypeCheck(char *filename);

/*
Disk* createObjectFromFile(int filetype);

void showDiskInfo(int filetype, char *filename);
*/
#endif