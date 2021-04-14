#ifndef EXT2_H
#define EXT2_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Disk.h"

using namespace std;

class Ext2 : public Disk
{
public:
    //Disk(void){};
    virtual int fileTypecheck(char *argv[]);
    virtual void getData(void);
};

#endif