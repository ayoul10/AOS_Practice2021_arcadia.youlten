#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include "Fat16.h"
#include "Ext2.h"

using namespace std;

#define OFFSET_FAT16 22
#define SIZE_FAT16 2
#define ELEMENTS_TO_READ_FAT16 1
#define FAT16_FILETYPE 0

#define OFFSET_EXT2 1080
#define SIZE_EXT2 2
#define ELEMENTS_TO_READ_EXT2 1
#define EXT2_FILETYPE 0xEF53

#define UNKNOWN -1
#define FAT16 0
#define EXT2 1

using namespace std;

#define BS_OEMNAME_OFFSET 3
#define BS_OEMNAME_BYTES 8
#define BPB_BYTSPERSEC_OFFSET 11
#define BPB_BYTSPERSEC_BYTES 2
#define BPB_SECPERCLUS_OFFSET 13
#define BPB_SECPERCLUS_BYTES 1
#define BPB_NUMFATS_OFFSET 16
#define BPB_NUMFATS_BYTES 1
#define BPB_ROOTENTCNT_OFFSET 17
#define BPB_ROOTENTCNT_BYTES 2
#define BPB_RSVDSECCNT 14
#define BPB_RSVDSECCNT_BYTES 2
#define BS_VOLLAB_OFFSET 43
#define BS_VOLLAB_BYTES 11

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


int fileTypeCheck(char *filename);
void showDiskInfo(char *filename);

#endif