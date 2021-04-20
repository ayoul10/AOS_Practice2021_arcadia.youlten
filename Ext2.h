#ifndef EXT2_H
#define EXT2_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Disk.h"

using namespace std;
//============= inode info ======================
#define INODE_INFO "INODE INFO: "
#define INODE_SIZE "Size: "
#define INODE_NUM "Num Inode: "
#define INODE_FIRST "First Inode: "
#define INODE_GROUP "Inodes Group: "
#define INODE_FREE "Inodes Free: "

//============= Block info ======================

#define BLOCK_INFO "BLOCK INFO: "
#define BLOCK_RESERVED "Blocks Reserved: "
#define BLOCK_FREE "Blocks Free: "
#define BLOCK_TOTAL "Blocks Total: "
#define BLOCK_FIRST "First Block: "
#define BLOCK_GROUP "Block Group: "
#define BLOCK_FRAG "Group Frags: "

//============= Volume info ======================
#define VOLUME_INFO "VOLUME INFO: "
#define VOLUME_NAME "Volume Name: "
#define VOLUME_CHECK "Last Check: "
#define VOLUME_LAST "Last: "
#define VOLUME_WRITE "Last Write: "

class Ext2 : public Disk
{
public:
    //Disk(void){};
    virtual void getData(void);
};

#endif