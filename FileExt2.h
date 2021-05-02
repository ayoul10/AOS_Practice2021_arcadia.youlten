#ifndef FILEEXT2_H
#define FILEEXT2_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Disk.h"
#include "Ext2.h"
#include <cstdio>
#include <fstream>
#include <string.h>
#include "FileManager.h"

using namespace std;

//================== EXT2 Defines =========================
#define SUPERBLOCK 1024
#define LASTWRITE 48
#define LASTCHECK 64
#define LASTMOUNT 44
#define VOLUMENAME 120
#define TOTALINODE 0
#define INODESGROUP 40
#define FIRSTINODE 84
#define INODESIZE 88
#define FREEINODE 2062
#define FREEBLOCK 12
#define BLOCKSIZE 24
#define RESERVEDBLOCK 8
#define TOTALBLOCK 4
#define FIRSTDATABLOCK 20
#define GROUPBLOCK 32
#define GROUPFRAG 36
#define VOLNAME 16

//=========== FIND DEFINES ===============================
#define ROOT_INODE_SUPERBLOCK 44
#define INODE_TABLE_OFFSET 8
#define FILESIZE_OFFSET 4
#define NAME_OFFSET 8
#define BLOCK_ARRAY 12
#define READABLE 1

class FileExt2
{
public:
    static Ext2 putFileInfoOnObjectExt2(char *filename);
    static void findExt2File(char *filename, char *diskname);

};

#endif