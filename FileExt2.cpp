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

int findFile(char *diskname, char *filename, int inode_number, int block_group_offset)
{

    Ext2 f = FileExt2::putFileInfoOnObjectExt2(diskname);
    int bg_inode_table;
    FILE *disk;
    int numerical_block_size = 1024 << f.blocksize;
    //superblock = offset past the superblock
    //numerical block size = skip first block that we're not interested in
    //inode table offset --> offset we need to read to determine the offset of the inode table
    int base_offset = SUPERBLOCK + INODE_TABLE_OFFSET + numerical_block_size;
    int filesize;
    int flag = 0;
    int dot = 0;
    disk = fopen(diskname, "r");

    //determine the block group number of the inode we want to reach
    int block_group_number = (inode_number -1 ) / f.inodespergroup;
    //get the inode's index within the block group 
    int local_inode_offset = ((inode_number - 1) % f.inodespergroup);

    //READ THE Locatoin OF THE INODE TABLE
    fseek(disk, block_group_offset, SEEK_SET);
    fread(&bg_inode_table, sizeof(int), 1, disk);
    rewind(disk);
    //this determines the offset of the inode table within the block group we want

    //BLOCK GROUP OFFSET IS CORRECT

    int block_group_start = 0;
    //Calculate the required block group
    block_group_start = (bg_inode_table * numerical_block_size) + (block_group_number * numerical_block_size * f.groupblock);

    int inode_table_offset = (local_inode_offset) * f.inodesize;

    int root_inode_block;
    int blocks_for_inode;

    //GET THE BLOCK WHERE THIS INFORMATION IS STORED
    fseek(disk, block_group_start + inode_table_offset + INODESGROUP, SEEK_SET);
    fread(&root_inode_block, sizeof(int), 1, disk);
    rewind(disk);

    //get PURE byte offset for this file
    int file_offset = root_inode_block * numerical_block_size;

    //we're at the start of the file
    int test;
    int inode;
    short rec_length;
    char name_len;
    char file_type;
    char name[255];
    int rec_length_counter = 0;
    int found = 0;

    while (rec_length_counter < numerical_block_size)
    {
        cleanString(name);

        fseek(disk, file_offset + rec_length_counter, SEEK_SET);
        fread(&inode, sizeof(int), 1, disk);
        fread(&rec_length, sizeof(short), 1, disk);
        fread(&name_len, sizeof(char), 1, disk);
        fread(&file_type, sizeof(char), 1, disk);
        fread((name), sizeof(name), 1, disk);

        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0 || inode == 11)
        {
            found = 0;
        }
        else if (file_type == 2)
        {
            int new_inode_local_offset = ((inode - 1) % f.inodespergroup);
            int block_group = ((inode - 1) / f.inodespergroup);
            int new_block_offset = base_offset + (block_group * numerical_block_size * f.groupblock);
            int directory_inode = inode;
            if (findFile(diskname, filename, inode, new_block_offset) == 0)
            {
                found = 0; 
            }
            else
            {
               return found = 1;
               break;
            }
        }
        else if (strcmp(name, filename) == 0)
        {
            found = 1;
            break;
        }

        rec_length_counter += rec_length;
        rewind(disk);
    }
    if (found == 1)
    {
        int inode_we_want = (inode - 1) * f.inodesize;
        fseek(disk, block_group_start + inode_we_want + 4, SEEK_SET);
        fread(&filesize, sizeof(int), 1, disk);
        rewind(disk);

        printf("File Found. it has %d number of bytes\n", filesize);
        return 1;
    }
    else
    {
        cout << "Unknown File " << endl;
        return 0;
    }
}

void FileExt2::findExt2File(char *filename, char *diskname)
{
    int numerical_block_size = 1024;
    for (int j = 0; filename[j] != '\0'; j++)
    {
        if (filename[j] >= 'A' && filename[j] <= 'Z')
        {
            filename[j] = filename[j] + 32;
        }
    }

    int j=0;
    int inode_number = 2;
    int block_group_offset = SUPERBLOCK + INODE_TABLE_OFFSET + numerical_block_size;
    int root =1;

    int found = findFile(diskname, filename, inode_number, block_group_offset);
}

void FileExt2::deleteExt2FileFromDisk(char *filename, char *diskname)
{
    std::cout << "Not Implemented Yet" << endl;
}
