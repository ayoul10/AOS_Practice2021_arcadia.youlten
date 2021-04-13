#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "errors.h"
using namespace std;

#define OFFSET_FAT16 19
#define SIZE_FAT16 2
#define ELEMENTS_TO_READ_FAT16 1
#define FAT16_FILETYPE 0

#define OFFSET_EXT2 1080
#define SIZE_EXT2 2
#define ELEMENTS_TO_READ_EXT2 1
#define EXT2_FILETYPE 0xEF53

/*
int volume_type(const char *fliename)
{
    //std::string file_information;

    //flag=1;
    fats16
    bytes:
    offset 19, size 2
        If(BPB_FATSz16 != 0)    FATSz = BPB_FATSz16;


return flag;
}
*/

//ext2 --> page 11 smagic
int command_line_error_check(int argc, char *argv[])
{
    int flag = 0;
    std::string command_wanted = "/info";
    //std::ifstream in(filename);

    if (argc < 3 || argc > 3)
    {
        cout << "Error! Too few or too many arguments!" << endl;
        return flag = 1;
    }
    //check if we're entering the correct command
    if (command_wanted.compare(argv[1]) != 0)
    {
        cout << "Unknown Command." << endl;
        cout << "Try entering /info" << endl;
        return flag = 1;
    }
    //check the file type
    else
    {
        FILE *file;
        int fat16 = 0;

        if (file = fopen(argv[2], "r"))
        {
            cout << "Opening " << argv[2] << "..." << endl;

            //check if FAT16
            fseek(file, OFFSET_FAT16, SEEK_SET);
            fread(&fat16, SIZE_FAT16, ELEMENTS_TO_READ_FAT16, file);

            if (fat16 != FAT16_FILETYPE)
            {
                cout << "Filetype is FAT16" << endl;
                return flag = 0;
            }

            rewind(file);
            int ext2 = 0;
            //check if EXT2
            fseek(file, OFFSET_EXT2, SEEK_SET);
            fread(&ext2, SIZE_EXT2, ELEMENTS_TO_READ_EXT2, file);

            if (ext2 == EXT2_FILETYPE)
            {
                cout << "Filetype is EXT2" << endl;
                return flag = 0;
            }
            else
            {
                cout << "Filetype not supported. Please upload a FAT16 or Ext2" << endl;
                return flag = 1;
            }

            fclose(file);
        }
        else
        {
            cout << "File Failed to Open" << endl;
            return flag = 1;
        }
    }
}

int main(int argc, char *argv[])
{

    if (command_line_error_check(argc, argv) == 1)
    {
        cout << "Ending program due to errors" << endl;
    }
    else
    {
        cout << "\nWe're successfully inside the program" << endl;
    }

    return 0;
}

//================================================================================
/*
// Create a text string, which is used to output the text file
string myText;

// Read from the text file
ifstream MyReadFile("filename.txt");

// Use a while loop together with the getline() function to read the file line by line
while (getline(MyReadFile, myText))
{
    // Output the text from the file
    cout << myText;
}

// Close the file
MyReadFile.close();


*/