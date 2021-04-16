#include "FileManager.h"
/*
Disk *createObjectFromFile(int filetype)
{
    if (filetype == FAT16)
    {
        return new Fat16;
    }
   
}
*/

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

void showDiskInfo(int filetype, char * filename){

    //Disk* disk = NULL; 
    FILE * file;
    int i;

    char *system_name = new char[64];
    short sector_size;
    char sectors_per_cluster;
    char fat_num;
    short max_root;
    short sectors_per_fat;
    short reserved_sec;
    char *volume_label = new char[88];
    //create object from file
    //disk = createObjectFromFile(filetype);

    //TODO:CHECK THE FILETYPE 

    file = fopen(filename, "r");

    cout << "Opening " << filename << "..." << endl;

    cout << FILESYSTEM_PRINT << endl;
    cout << FILESYSTEM_TYPE << " Fat16" << endl;

    fseek(file, BS_OEMNAME_OFFSET, SEEK_SET);
    fread((void *)(system_name), sizeof(char), BS_OEMNAME_BYTES, file);
    std::cout << FILESYSTEM_NAME << system_name << endl;

    rewind(file);
    fflush(0);

    fseek(file, BPB_BYTSPERSEC_OFFSET, SEEK_SET);
    fread(&sector_size, sizeof(short), 1, file);
    cout << SECTOR_SIZE << sector_size << endl;

    rewind(file);
    fflush(0);

    fseek(file, BPB_SECPERCLUS_OFFSET, SEEK_SET);
    fread(&sectors_per_cluster, sizeof(char), 1, file);
    printf("%s", SECTOR_COUNT_CLUSTER);
    printf(" %u \n", sectors_per_cluster);

    rewind(file);
    fflush(0);

    fseek(file, BPB_RSVDSECCNT, SEEK_SET);
    fread(&reserved_sec, sizeof(short), 1, file);
    cout << RESERVED_SECTOR << reserved_sec << endl;

    rewind(file);
    fflush(0);

    fseek(file, BPB_NUMFATS_OFFSET, SEEK_SET);
    fread(&fat_num, sizeof(char), 1, file);
    printf("%s", FAT_COUNT);
    printf("%u \n", fat_num);

    rewind(file);
    fflush(0);

    fseek(file, BPB_ROOTENTCNT_OFFSET, SEEK_SET);
    fread(&max_root, sizeof(short), 1, file);
    cout << ROOT_MAX << max_root << endl;

    rewind(file);
    fflush(0);

    fseek(file, OFFSET_FAT16, SEEK_SET);
    fread(&sectors_per_fat, sizeof(short), 1, file);
    printf("%s", SECTOR_COUNT_FAT);
    printf("%i\n", sectors_per_fat);

    rewind(file);
    fflush(0);

    fseek(file, BS_VOLLAB_OFFSET, SEEK_SET);
    fread((void *)(volume_label), sizeof(char), BS_VOLLAB_BYTES, file);
    std::cout << LABEL << volume_label << endl;


    //read the file and store it in the disk object
    //print the disk info
    delete[] system_name;
    delete[] volume_label;
    fclose(file);
    }