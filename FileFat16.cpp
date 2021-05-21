#include "FileFat16.h"

Fat16 FileFat16::putFileInfoOnObjectFat16(char *filename)
{
    Fat16 fat16;

    FILE *file;
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
//locate the file in the root directory

//Root Directory Location
//offset?
//FirstRootDirSecNum = BPB_ResvdSecCnt + (BPB_NumFATs * BPB_FATSz16);

//Each directory consists of a number of fixed-size entries.
//Each entry is 32 bytes long.
//The number of sectors in the directory is fixed for the root directory on FAT12 and FAT16 partitions
//and sectors are consecutive on disk

//first cluster * sector size * sector count

bool findFile(char *diskname, char *filename, int directory_offset, int cluster_size, int data_start)
{
    char filewewant[9];
    char fileextension[4];
    char namewithextension[13];
    unsigned char attribute;
    int flag = 0;
    int dot = 0;
    int filesize =0;
    int i = 0;
    unsigned short clus = 0;
    FILE *disk;

    disk = fopen(diskname, "r");

    while (filewewant[0] != 0x00)
    {
        int j = 0;
        int k = 0;
        dot = 0;
        //clean strings
        cleanString(namewithextension);
        cleanString(fileextension);
        cleanString(filewewant);
        clus =0;
        attribute = '\0';

        fseek(disk, directory_offset +i, SEEK_SET);
        fread(filewewant, sizeof(char), 8, disk);
        fread(fileextension, sizeof(char), 3, disk);
        fread(&attribute, sizeof(char), 1, disk);
        fseek(disk, START_CLUSTER_OFFSET, SEEK_CUR);
        fread(&clus, sizeof(short), 1, disk);
        j = 0;
        k = 0;
        filewewant[8] = '\0';
        fileextension[3] = '\0';

        if ((attribute == 0xF) || (filewewant[0] == '.') || (strcmp(filewewant, "..") == 0))
        {
            i+=32;//move on to the next entry?
        }
        else if ((attribute == 0x10))
        {
            rewind(disk);
            clus = clus - 2;
            int new_directory_offset = (clus * cluster_size) + data_start;
            //THERE'S A BUNCH OF JUNK INBETWEEN
            //fclose(disk);
            if (!findFile(diskname, filename, new_directory_offset, cluster_size, data_start))
            {
                j = 0;
                k = 0;
                dot = 0;
                i += 32;
            }
            else
            {
                return flag = 1;
                break;
            }
        }
        else{
                j = 0;
                k = 0;
                dot =0;
            for (int j = 0; j < 12; j++)
            {
                if (j < 8 && (filewewant[j] != ' '))
                {
                    namewithextension[j] = filewewant[j];
                }
                //if we haven't put a dot, and we've found a space, or we're at the max value for the name
                else if (dot != 1 && (j == 8 || filewewant[j] == ' ') && fileextension[0] != ' ')
                {
                    namewithextension[j] = '.';
                    dot = 1;
                }
                else if (k < 3 && fileextension[k] != ' ')
                {
                    namewithextension[j] = fileextension[k];
                    k++;
                }
                else if (k == 3 || fileextension[k] == ' ' || fileextension[k] == '\0')
                {
                    namewithextension[j] = '\0';
                }
            }

            j = 0;
            k = 0;

            if (strcmp(filename, namewithextension) == 0)
            {
                //fseek(disk, FILE_SIZE_OFFSET + 1, SEEK_CUR);
                fread(&filesize, sizeof(int), 1, disk);

                printf("File Found. it has %d number of bytes\n", filesize);
                fclose(disk);

                return flag = 1;
            }

            i += 32; //32 or 64 works?????

            
        }
        rewind(disk);
    }
    fclose(disk);
    
    return flag =0;
}

void FileFat16::findFat16File(char *filename, char *diskname)
{
    Fat16 f = FileFat16::putFileInfoOnObjectFat16(diskname);
    int i=0;

    int firstrootdirsecnum = (f.reserved_sec * f.sector_size) + (f.fat_num * f.sectors_per_fat * f.sector_size);
    int root_dir_size = (f.max_root * 32);
    int data_start = firstrootdirsecnum + root_dir_size;
    int cluster_size = f.sector_size * f.sectors_per_cluster;

    //conver filename to upper case so we can compare it

    for (int j = 0; filename[j] != '\0'; j++)
    {
        if (filename[j] >= 'a' && filename[j] <= 'z')
        {
            filename[j] = filename[j] - 32;
        }
    }
    //!findFile(diskname, filename, firstrootdirsecnum, i=64) &&
    if (!findFile(diskname, filename, firstrootdirsecnum, cluster_size, data_start))
    {
        std::cout << "Could not find file on disk" << endl;
    }

}

void FileFat16::deleteFat16FileFromDisk(char *filename, char *diskname)
{
    std::cout << "In progress" << endl;
}
