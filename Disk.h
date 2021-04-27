#ifndef DISK_H
#define DISK_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Disk
{

    virtual void printData() = 0;
    virtual void printFileMetaData() = 0;
};


#endif