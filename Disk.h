#ifndef DISK_H
#define DISK_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define FILESYSTEM_PRINT "------ Filesystem Information ------"
#define FILESYSTEM_TYPE "Filesystem: "

//object manager class?
class Disk
{
public:
    Disk(void){};
    virtual void getData(void) = 0;
};


#endif