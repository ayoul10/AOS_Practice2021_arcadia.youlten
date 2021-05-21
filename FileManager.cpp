#include "FileManager.h"

int fileTypeCheck(char *filename)
{
    int filetype;
    FILE *file;
    char *fat16string = new char[8];

    if (file = fopen(filename, "r"))
    {

        fseek(file, 54, SEEK_SET);
        fread((void *)(fat16string), sizeof(char), 8, file);

        if (strcmp(fat16string, "FAT16   ") == 0)
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
            Fat16 fat16 = FileFat16::putFileInfoOnObjectFat16(filename);
            fat16.printData();
        }
        else if (filetype == EXT2){

            Ext2 ext2 = FileExt2::putFileInfoOnObjectExt2(filename);
            ext2.printData();
        }
        else{
            cout << "Ending Program Due to Errors" << endl;
        }
    }
void findFileonDisk(char * diskname, char * filename){

    int filetype = fileTypeCheck(diskname);
    if (filetype == FAT16)
    {
        bool result = FileFat16::findFat16File(filename, diskname);
    }
    else if (filetype == EXT2)
    {
        FileExt2::findExt2File(filename, diskname);
    }
    else
    {
        cout << "Ending Program Due to Errors" << endl;
    }
}

void deleteFileFromDisk(char *diskname, char *filename)
{

    int filetype = fileTypeCheck(diskname);
    if (filetype == FAT16)
    {
        FileFat16::deleteFat16FileFromDisk(filename, diskname);
    }
    else if (filetype == EXT2)
    {
        FileExt2::deleteExt2FileFromDisk(filename, diskname);
    }
    else
    {
        cout << "Ending Program Due to Errors" << endl;
    }
}

void cleanString(char *string){

    for(int i=0; i<sizeof(string); i++){
        string[i] = '\0';
    }
}
