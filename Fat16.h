#ifndef FAT16_H
#define FAT16_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Disk.h"

using namespace std;

class Fat16 : public Disk
{
    public: 
        void printData() override;

        char *system_name = new char[64];
        short sector_size;
        char sectors_per_cluster;
        char fat_num;
        short max_root;
        short sectors_per_fat;
        short reserved_sec;
        char *volume_label = new char[88];
};

#endif

