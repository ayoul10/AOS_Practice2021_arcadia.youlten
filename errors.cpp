#include "errors.h"

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
        int fat16;
        if (file = fopen(argv[2], "r")){
            fclose(file);
            printf("Opening %s...", argv[2]);

            //check if FAT16
            fseek(file, OFFSET_FAT16, SEEK_SET);
            fread(&fat16, SIZE_FAT16, ELEMENTS_TO_READ_FAT16, file);
            if (fat16 !=0){
                cout << "Filetype is FAT16" << endl;
                return flag = 0; 
            }
            else{
                cout << "What the heck is this" << endl;
                return flag = 1;
            }
        }  
        else
        {
            cout << "File Failed to Open" << endl;
            return flag = 1;
        }

        
        /*
        if (!in)
        {
            std::cerr << filename << " failed to open\n";
            return flag = 1;
        }
        else
        {
            // Read a character, test for end-of-file
            bool empty = (in.get(), in.eof());
            if (empty == true)
            {
                cout << "Error: empty file" << endl;
                return flag = 1;
            }

            open(filename);

            //check if we have an (EXT2 or FAT16)
            //size_t file_info;
            //int flag =0;
            //
            //
            /*
            else if ()
            {
                cout << "Error: File system is neither EXT2 nor FAT16" << endl;
                return flag =1; 
            }
            else{
                return flag;
            }
            */
    }
}