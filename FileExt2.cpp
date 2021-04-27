#include "FileExt2.h"

Ext2 FileExt2::putFileInfoOnObjectExt2(char *filename)
{
    Ext2 ext2;

    FILE *file;
    int i;

    file = fopen(filename, "r");

    fseek(file, VOLUMENAME + SUPERBLOCK, SEEK_SET);
    fread((void *)(ext2.volume_name), sizeof(char), VOLNAME, file);

    rewind(file);
    fflush(0);

    fseek(file, LASTWRITE + SUPERBLOCK, SEEK_SET);
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
void FileExt2::findExt2File(char *filename, char *diskname)
{
    cout << "Not implemented Yet" << endl;
}