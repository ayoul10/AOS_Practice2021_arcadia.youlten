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
   //Disk(void){};
    virtual int fileTypecheck(char *argv[]);
    virtual void getData(void);
};

#endif

