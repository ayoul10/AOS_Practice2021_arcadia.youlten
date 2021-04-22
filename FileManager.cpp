#include "FileManager.h"

Fat16 putFileInfoOnObject(char * filename){

    Fat16 fat16;
    char *system_name = new char[64];
    short sector_size;
    char sectors_per_cluster;
    char fat_num;
    short max_root;
    short sectors_per_fat;
    short reserved_sec;
    char *volume_label = new char[88];

    FILE *file;
    //TODO: Decide if i want to 1) create object first, then add fields
    int i;

    file = fopen(filename, "r");
        
        fseek(file, BS_OEMNAME_OFFSET, SEEK_SET);
        fread((void *)(fat16.system_name), sizeof(char), BS_OEMNAME_BYTES, file);

        rewind(file);
        fflush(0);

        fseek(file, BPB_BYTSPERSEC_OFFSET, SEEK_SET);
        fread(&fat16.sector_size, sizeof(short), 1, file);

        rewind(file);
        fflush(0);

        fseek(file, BPB_SECPERCLUS_OFFSET, SEEK_SET);
        fread(&fat16.sectors_per_cluster, sizeof(char), 1, file);
       

        rewind(file);
        fflush(0);

        fseek(file, BPB_RSVDSECCNT, SEEK_SET);
        fread(&fat16.reserved_sec, sizeof(short), 1, file);

        rewind(file);
        fflush(0);

        fseek(file, BPB_NUMFATS_OFFSET, SEEK_SET);
        fread(&fat16.fat_num, sizeof(char), 1, file);

        rewind(file);
        fflush(0);

        fseek(file, BPB_ROOTENTCNT_OFFSET, SEEK_SET);
        fread(&fat16.max_root, sizeof(short), 1, file);
        rewind(file);
        fflush(0);

        fseek(file, OFFSET_FAT16, SEEK_SET);
        fread(&fat16.sectors_per_fat, sizeof(short), 1, file);

        rewind(file);
        fflush(0);

        fseek(file, BS_VOLLAB_OFFSET, SEEK_SET);
        fread((void *)(fat16.volume_label), sizeof(char), BS_VOLLAB_BYTES, file);
        fclose(file);

        return fat16;
}

Ext2 putFileInfoOnObjectExt2(char *filename)
{
    Ext2 ext2;

    FILE *file;
    //TODO: Decide if i want to 1) create object first, then add fields
    int i;

    file = fopen(filename, "r");

    fseek(file, VOLUMENAME + SUPERBLOCK, SEEK_SET);
    fread((void *)(ext2.volume_name), sizeof(char), VOLNAME, file);

    rewind(file);
    fflush(0);

    fseek(file, LASTWRITE+SUPERBLOCK, SEEK_SET);
    fread((&ext2.lastwrite), sizeof(int), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, LASTCHECK + SUPERBLOCK, SEEK_SET);
    fread((&ext2.lastcheck), sizeof(int), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, LASTMOUNT + SUPERBLOCK, SEEK_SET);
    fread((&ext2.lastmount), sizeof(int), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, TOTALINODE + SUPERBLOCK, SEEK_SET);
    fread(&ext2.toatlnuminodes, sizeof(int), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, INODESGROUP + SUPERBLOCK, SEEK_SET);
    fread(&ext2.inodespergroup, sizeof(int), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, FIRSTINODE + SUPERBLOCK, SEEK_SET);
    fread(&ext2.firstinode, sizeof(int), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, FREEINODE, SEEK_SET);
    fread(&ext2.freeinode, sizeof(short), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, FREEBLOCK + SUPERBLOCK, SEEK_SET);
    fread(&ext2.freeblock, sizeof(int), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, INODESIZE + SUPERBLOCK, SEEK_SET);
    fread(&ext2.inodesize, sizeof(short), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, BLOCKSIZE + SUPERBLOCK, SEEK_SET);
    fread(&ext2.blocksize, sizeof(int), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, RESERVEDBLOCK + SUPERBLOCK, SEEK_SET);
    fread(&ext2.reservedblock, sizeof(int), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, TOTALBLOCK + SUPERBLOCK, SEEK_SET);
    fread(&ext2.totalblock, sizeof(int), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, FIRSTDATABLOCK + SUPERBLOCK, SEEK_SET);
    fread(&ext2.firstblock, sizeof(int), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, GROUPBLOCK + SUPERBLOCK, SEEK_SET);
    fread(&ext2.groupblock, sizeof(int), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, GROUPFRAG + SUPERBLOCK, SEEK_SET);
    fread(&ext2.fraggroup, sizeof(int), 1, file);

    fclose(file);

    return ext2;
}

int fileTypeCheck(char *filename)
{

    int filetype;
    FILE *file;
    int fat16 = 0;

    if (file = fopen(filename, "r"))
    {
        cout << "Opening " << filename << "..." << endl;

        //check if FAT16
        fseek(file, OFFSET_FAT16, SEEK_SET);
        fread(&fat16, SIZE_FAT16, ELEMENTS_TO_READ_FAT16, file);

        if (fat16 != FAT16_FILETYPE)
        {
            return FAT16;
        }

        rewind(file);
        int ext2 = 0;
        //check if EXT2
        fseek(file, OFFSET_EXT2, SEEK_SET);
        fread(&ext2, SIZE_EXT2, ELEMENTS_TO_READ_EXT2, file);

        if (ext2 == EXT2_FILETYPE)
        {
            return EXT2;
        }
        else
        {
            cout << "Filetype not supported. Please upload a FAT16 or Ext2" << endl;
            return UNKNOWN;
        }

        fclose(file);
    }
    else
    {
        cout << "File Failed to Open" << endl;
        return UNKNOWN;
    }
}

void showDiskInfo(char * filename){

    int filetype = fileTypeCheck(filename);
        if(filetype == FAT16){
            Fat16 fat16 = putFileInfoOnObject(filename);
            fat16.printData();
        }
        else{

            Ext2 ext2 = putFileInfoOnObjectExt2(filename);
            ext2.printData();
        }

    }
