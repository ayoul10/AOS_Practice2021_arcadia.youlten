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
    Ext2 f = FileExt2::putFileInfoOnObjectExt2(diskname);
    FILE *disk;
    int numerical_block_size = 1024 << f.blocksize;
    int filesize;
    int flag = 0;
    int dot = 0;

    for (int j = 0; filename[j] != '\0'; j++)
    {
        if (filename[j] >= 'A' && filename[j] <= 'Z')
        {
            filename[j] = filename[j] + 32;
        }
    }

    int j=0;
    int bg_inode_table;
    int inode_number;

    disk = fopen(diskname, "r");

    //root directory inode = inode 2
    fseek(disk, SUPERBLOCK + INODE_TABLE_OFFSET + numerical_block_size, SEEK_SET);
    fread(&bg_inode_table, sizeof(int), 1, disk);
    rewind(disk);

    int inode_table_start = bg_inode_table * numerical_block_size;
    int root_inode_offset = (f.firstinode-1) * f.inodesize;
    //for now, this works since we're in the root directory
    //int root_inode_offset = (2- 1) * f.inodesize;t
    int root_inode_block;
    int blocks_for_inode;

    fseek(disk, inode_table_start + root_inode_offset + 40, SEEK_SET);
    fread(&root_inode_block, sizeof(int), 1, disk);
    rewind(disk);

    root_inode_block--;

    int file_offset = root_inode_block * numerical_block_size;

    //we're at the start of the file
    int test;
    int inode;
    short rec_length;
    char name_len;
    char file_type;
    char name[255];
    int rec_length_counter=0;
    int found=0;

    while (rec_length_counter < numerical_block_size)
    {
        cleanString(name);

        fseek(disk, file_offset + rec_length_counter, SEEK_SET);
        fread(&inode, sizeof(int), 1, disk);
        fread(&rec_length, sizeof(short), 1, disk);
        fread(&name_len, sizeof(char), 1, disk);
        fread(&file_type, sizeof(char), 1, disk);
        fread((name), sizeof(name), 1, disk);

        if (strcmp(name, filename) == 0)
        {
            found = 1;
            break;
        }

        rec_length_counter += rec_length;
        rewind(disk);
    }
    if (file_type != READABLE)
    {
        printf("Input found, but it is not a file\n");
    }
    else if (found == 1)
    {
        int inode_we_want = (inode - 1) * f.inodesize;
        fseek(disk, inode_table_start + inode_we_want + 4, SEEK_SET);
        fread(&filesize, sizeof(int), 1, disk);
        rewind(disk);

        printf("File Found. it has %d number of bytes\n", filesize);
    }
    else
    {
        cout << "Unknown File " << endl;
    }

}
