#ifndef FAT16_H
#define FAT16_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Disk.h"

using namespace std;
#define FILESYSTEM_NAME "System Name: "
#define FILE_SIZE "Size: "
#define SECTOR_COUNT_CLUSTER "Sectors Per Cluster: "
#define FAT_COUNT "Number of FATS: "
#define ROOT_MAX "Max Root Entries: "
#define SECTOR_COUNT_FAT "Sectors Per Fat: "
#define LABEL "Label: "

class Fat16 : public Disk
{
public:
   //Disk(void){};
    virtual void getData(void);
};

#endif

