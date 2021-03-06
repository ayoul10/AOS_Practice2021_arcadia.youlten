#include "FileExt2.h"

storage_for_inodes inode_storage[2];
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

int findFile(char *diskname, char *filename, int inode_number, int block_group_offset, int remove)
{

    Ext2 f = FileExt2::putFileInfoOnObjectExt2(diskname);
    int bg_inode_table;
    FILE *disk;
    int numerical_block_size = 1024 << f.blocksize;
    int block_numbers_array[12];
    //superblock = offset past the superblock
    //numerical block size = skip first block that we're not interested in
    //inode table offset --> offset we need to read to determine the offset of the inode table
    int base_offset = SUPERBLOCK + INODE_TABLE_OFFSET + numerical_block_size;
    int filesize;
    int flag = 0;
    int dot = 0;
    disk = fopen(diskname, "r+");

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

    //get the number of blocks reserved for this inode
    fseek(disk, block_group_start + inode_table_offset + BLOCK_INODES, SEEK_SET);
    fread(&blocks_for_inode, sizeof(int), 1, disk);
    rewind(disk);

    int file_offsets[12];

    for (int m = 0; m < blocks_for_inode; m++)
    {
        fseek(disk, block_group_start + inode_table_offset + (INODESGROUP + (m*4)), SEEK_SET);
        fread(&block_numbers_array[m], sizeof(int), 1, disk);
        rewind(disk);
        file_offsets[m] = block_numbers_array[m] * numerical_block_size;
    }
    //get PURE byte offset for this file

    //we're at the start of the file
    int test;
    int junk=0;
    int inode;
    short rec_length;
    char name_len;
    char file_type;
    char name[255];
    int current_block=0;
    int trash; 
    
    int found = 0;
    int mod_counter =0;
    int block_counter = 0;
    int rec_length_counter=0;

    for(block_counter=0; block_counter < blocks_for_inode && found !=1 ; block_counter++){
        rec_length_counter = 0;
        while (rec_length_counter < numerical_block_size && found != 1 && block_numbers_array[block_counter] != 0)
        {
            cleanString(name);
            name_len=0;
            rec_length=0;

            fseek(disk, file_offsets[block_counter] + rec_length_counter, SEEK_SET);
            fread(&inode, sizeof(int), 1, disk);
            fread(&rec_length, sizeof(short), 1, disk);
            fread(&name_len, sizeof(char), 1, disk);
            fread(&file_type, sizeof(char), 1, disk);
            fread((name), name_len, 1, disk);
            name[name_len] = '\0';
            current_block = block_counter;

            if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0 || inode == 11)
            {
                found = 0;
            }
            else if (file_type == 2){
                int new_inode_local_offset = ((inode - 1) % f.inodespergroup);
                int block_group = ((inode - 1) / f.inodespergroup);
                int new_block_offset = base_offset + (block_group * numerical_block_size * f.groupblock);
                int directory_inode = inode;
                    if (findFile(diskname, filename, inode, new_block_offset, remove) == 0)
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
                inode_storage[mod_counter % 2].inode = inode;
                inode_storage[mod_counter % 2].rec_length = rec_length;
                inode_storage[mod_counter % 2].name_len = name_len;
                inode_storage[mod_counter % 2].file_type = file_type;
                inode_storage[mod_counter % 2].block_number = block_counter;
                cleanString(inode_storage[mod_counter % 2].name);
                strcpy(inode_storage[mod_counter % 2].name, name);
                
                break;
            }

            inode_storage[mod_counter % 2].inode = inode;
            inode_storage[mod_counter % 2].rec_length = rec_length;
            inode_storage[mod_counter % 2].block_number = block_counter;
            inode_storage[mod_counter % 2].name_len = name_len;
            inode_storage[mod_counter % 2].file_type = file_type;
            cleanString(inode_storage[mod_counter % 2].name);
            strcpy(inode_storage[mod_counter % 2].name, name);
            mod_counter++;
            rec_length_counter += rec_length;
            rewind(disk);
        }
    }
    if (found == 1)
    {
        if (remove == 1){

            rewind(disk);
            if (inode_storage[mod_counter % 2].block_number == inode_storage[(mod_counter-1) % 2].block_number)
            {
                short rec_length_to_override = inode_storage[(mod_counter - 1) % 2].rec_length + inode_storage[mod_counter % 2].rec_length;
                short previous_entry = rec_length_counter - inode_storage[(mod_counter - 1) % 2].rec_length;
                fseek(disk, file_offsets[block_counter - 1] + previous_entry, SEEK_SET);
                fwrite(&junk, sizeof(int), 1, disk);
                fwrite(&rec_length_to_override, sizeof(short), 1, disk);
            }
            else{

                int old_rec_length = rec_length_counter;
                rec_length_counter += rec_length;

                int new_inode;
                short new_rec_length;
                char new_name_len;
                char new_file_type;
                char new_name[255];

                fseek(disk, file_offsets[block_counter] + rec_length_counter, SEEK_SET);
                fread(&new_inode, sizeof(int), 1, disk);
                fread(&new_rec_length, sizeof(short), 1, disk);
                fread(&new_name_len, sizeof(char), 1, disk);
                fread(&new_file_type, sizeof(char), 1, disk);
                fread((new_name), sizeof(new_name), 1, disk);

                rewind(disk);

                fseek(disk, file_offsets[block_counter-1] + old_rec_length, SEEK_SET);
                fwrite(&new_inode, sizeof(int), 1, disk);
                fwrite(&new_rec_length, sizeof(short), 1, disk);
                fwrite(&new_name_len, sizeof(char), 1, disk);
                fwrite(&new_file_type, sizeof(char), 1, disk);
                fwrite((new_name), sizeof(new_name), 1, disk);
            }

            rewind(disk);

            printf("The file %s has been deleted \n", name);
        }
        else{
            rewind(disk);
            int inode_we_want = (((inode - 1) % f.inodespergroup)* f.inodesize);
            fseek(disk, block_group_start+ inode_we_want + 4, SEEK_SET);
            fread(&filesize, sizeof(int), 1, disk);
            rewind(disk);
            
            printf("File Found. it has %d number of bytes\n", filesize);
        }
        return 1; 
    }
    else
    {
        return 0;
    }
}

void FileExt2::findExt2File(char *filename, char *diskname, int remove)
{
    int numerical_block_size = 1024;

    int j=0;
    int inode_number = 2;
    int block_group_offset = SUPERBLOCK + INODE_TABLE_OFFSET + numerical_block_size;
    int root =1;

    filename[strlen(filename)] = '\0';

    int found = findFile(diskname, filename, inode_number, block_group_offset, remove);
    if(found == 0){
        cout << "Unknown File " << endl;
    }
}

