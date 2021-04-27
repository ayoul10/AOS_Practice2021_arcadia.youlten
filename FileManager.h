#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string.h>
#include "Fat16.h"
#include "Ext2.h"
#include "FileExt2.h"
#include "FileFat16.h"

using namespace std;

#define FAT16_FILE_OFFSET 54
#define FAT16_FILE_READ 8
#define ELEMENTS_TO_READ_FAT16 1
#define FAT16_FILETYPE "FAT16   "

#define OFFSET_EXT2 1080
#define SIZE_EXT2 2
#define ELEMENTS_TO_READ_EXT2 1
#define EXT2_FILETYPE 0xEF53

#define UNKNOWN -1
#define FAT16 0
#define EXT2 1

int fileTypeCheck(char *filename);
void showDiskInfo(char *filename);
void findFileonDisk(char *diskname, char *filename);

#endif