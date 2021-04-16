#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <fstream>
//#include "Fat16.h"
//#include "Ext2.h"
//#include "Disk.h"

using namespace std;

#define OFFSET_FAT16 22
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

using namespace std;

#define FILESYSTEM_PRINT "------ Filesystem Information ------"
#define FILESYSTEM_TYPE "Filesystem: "
#define FILESYSTEM_NAME "System Name: "              //BS_OEMName offset 3, 8 bytes
#define SECTOR_SIZE "Sector Size: "                           //
#define RESERVED_SECTOR "Reserved Sectors: "        //
#define SECTOR_COUNT_CLUSTER "Sectors Per Cluster: " //BPB_SecPerClus offset 11, 2 bytes
#define FAT_COUNT "Number of FATS: "                 //BPB_NumFATs offset 16, 1 byte
#define ROOT_MAX "Max Root Entries: "                //BPB_RootEntCnt offset 17, 2 bytes
#define SECTOR_COUNT_FAT "Sectors Per Fat: "         //BPB_FATSz16 offset 22, 2 bytes
#define LABEL "Label: "                              //Label: offset 43, 11 bytes

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
#define BPB_ROOTENTCNT_OFFSET 17
#define BPB_ROOTENTCNT_BYTES 2
#define BPB_RSVDSECCNT 14
#define BPB_RSVDSECCNT_BYTES 2
#define BS_VOLLAB_OFFSET 43
#define BS_VOLLAB_BYTES 11
int fileTypeCheck(char *filename);

//Disk* createObjectFromFile(int filetype);

void showDiskInfo(int filetype, char *filename);

#endif