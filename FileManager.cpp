#include "FileManager.h"

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
            cout << "Filetype is FAT16" << endl;
            return FAT16;
        }

        rewind(file);
        int ext2 = 0;
        //check if EXT2
        fseek(file, OFFSET_EXT2, SEEK_SET);
        fread(&ext2, SIZE_EXT2, ELEMENTS_TO_READ_EXT2, file);

        if (ext2 == EXT2_FILETYPE)
        {
            cout << "Filetype is EXT2" << endl;
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