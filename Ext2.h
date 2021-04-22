#ifndef EXT2_H
#define EXT2_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <time.h>
#include "Disk.h"

using namespace std;

#define FILESYSTEM_PRINT "------ Filesystem Information ------"
#define FILESYSTEM_TYPE "Filesystem: "
//============= inode info ======================
#define INODE_INFO "INODE INFO: "
#define INODE_SIZE "Inode Size: " //s_inode_size
#define INODE_NUM "Num Inode: " //s_inodes_count
#define INODE_FIRST "First Inode: " //s_first_ino
#define INODE_GROUP "Inodes Group: "//s_inodes_per_group
#define INODE_FREE "Inodes Free: "//bg_gree_inodes_count

//============= Block info ======================

#define BLOCK_INFO "BLOCK INFO: "
#define BLOCK_RESERVED "Blocks Reserved: " //s_r_block_count
#define BLOCK_FREE "Blocks Free: " //s_free_blocks_count
#define BLOCK_TOTAL "Blocks Total: "//s_blocks_count
#define BLOCK_FIRST "First Block: "//s_first_data_block
#define BLOCK_GROUP "Block Group: "//s_block_per_group
#define BLOCK_FRAG "Group Frags: " //s_frags_per_group
#define BLOCK_SIZE "Block Size: "

//============= Volume info ======================
#define VOLUME_INFO "VOLUME INFO: "
#define VOLUME_NAME "Volume Name: " //s_volume_name
#define VOLUME_CHECK "Last Check: " //s_lastcheck
#define VOLUME_LAST "Last Mounted: " //s_mtime
#define VOLUME_WRITE "Last Write: " //s_wtime

class Ext2 : public Disk
{

    public:
        void printData() override;

        int lastwrite;
        int lastcheck;
        int lastmount;

        char *volume_name = new char[16];
        int toatlnuminodes;
        int inodespergroup;
        int firstinode;
        short freeinode;
        short inodesize;
        int freeblock;
        int blocksize;
        int reservedblock;
        int totalblock;
        int firstblock;
        int groupblock;
        int fraggroup;
};

#endif