#include "Fat16.h"

#define FILESYSTEM_PRINT "------ Filesystem Information ------"
#define FILESYSTEM_TYPE "Filesystem: "
#define FILESYSTEM_NAME "System Name: "
#define SECTOR_SIZE "Sector Size: "                  //
#define RESERVED_SECTOR "Reserved Sectors: "         //
#define SECTOR_COUNT_CLUSTER "Sectors Per Cluster: " //BPB_SecPerClus offset 11, 2 bytes
#define FAT_COUNT "Number of FATS: "                 //BPB_NumFATs offset 16, 1 byte
#define ROOT_MAX "Max Root Entries: "                //BPB_RootEntCnt offset 17, 2 bytes
#define SECTOR_COUNT_FAT "Sectors Per Fat: "         //BPB_FATSz16 offset 22, 2 bytes
#define LABEL "Label: "                              //Label: offset 43, 11 bytes

void Fat16::printData()
{
    std::cout << FILESYSTEM_PRINT << endl;
    std::cout << FILESYSTEM_TYPE << "FAT16" << endl;
    std::cout << FILESYSTEM_NAME << this->system_name << endl;
    cout << SECTOR_SIZE << this->sector_size << endl;
    printf("%s", SECTOR_COUNT_CLUSTER);
    printf(" %u \n", this->sectors_per_cluster);
    cout << RESERVED_SECTOR << this->reserved_sec << endl;
    printf("%s", FAT_COUNT);
    printf("%u \n", this->fat_num);
    cout << ROOT_MAX << this->max_root << endl;
    printf("%s", SECTOR_COUNT_FAT);
    printf("%i\n", this->sectors_per_fat);
    std::cout << LABEL << this->volume_label << endl;
}
