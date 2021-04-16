#ifndef FAT16_H
#define FAT16_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Disk.h"

using namespace std;
#define FILESYSTEM_NAME "System Name: "                //BS_OEMName offset 3, 8 bytes
#define FILE_SIZE "Size: "                             //
#define SECTOR_COUNT_CLUSTER "Sectors Per Cluster: " //BPB_SecPerClus offset 11, 2 bytes
#define FAT_COUNT "Number of FATS: "                 //BPB_NumFATs offset 16, 1 byte
#define ROOT_MAX "Max Root Entries: "                //BPB_RootEntCnt offset 17, 2 bytes
#define SECTOR_COUNT_FAT "Sectors Per Fat: "         //BPB_FATSz16 offset 22, 2 bytes
#define LABEL "Label: "                             //Label: offset 43, 11 bytes

#define BS_OEMNAME_OFFSET 3
#define BS_OEMNAME_BYTES 8
//size defines
//#define BS_OEMNAME_OFFSET 3
//#define BS_OEMNAME_OFFSET 3
#define BPB_SECPERCLUS_OFFSET 11
#define BPB_SECPERCLUS_BYTES 2
#define BPB_NUMFATS_OFFSET 16
#define BPB_NUMFATS_BYTES 1
#define BPB_ROOTENTCNT_OFFSET 17
#define BPB_ROOTENTCNT_BYTES 2

class Fat16 : public Disk
{
public:
   //Disk(void){};
    void getData(void);

    char * system_name;
    int size;
    int sectors_per_cluster;
    int fat_num;
    int max_root;
    int sectors_per_fat;
    char * volume_label;

    
};

#endif

