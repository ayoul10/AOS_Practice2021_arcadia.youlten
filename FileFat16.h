#ifndef FILEFAT16_H
#define FILEFAT16_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Disk.h"
#include "Fat16.h"
#include <cstdio>
#include <fstream>
#include <string.h>
#include "FileManager.h"
using namespace std;

#define BS_OEMNAME_OFFSET 3
#define BS_OEMNAME_BYTES 8
#define BPB_BYTSPERSEC_OFFSET 11
#define BPB_BYTSPERSEC_BYTES 2
#define BPB_SECPERCLUS_OFFSET 13
#define BPB_SECPERCLUS_BYTES 1
#define BPB_NUMFATS_OFFSET 16
#define BPB_NUMFATS_BYTES 1
#define BPB_ROOTENTCNT_OFFSET 17
#define BPB_ROOTENTCNT_BYTES 2
#define BPB_RSVDSECCNT 14
#define BPB_RSVDSECCNT_BYTES 2
#define BS_VOLLAB_OFFSET 43
#define BS_VOLLAB_BYTES 11
#define OFFSET_FAT16 22
#define SIZE_FAT16 2
class FileFat16
{
public:
    static Fat16 putFileInfoOnObjectFat16(char *filename);
};

#endif