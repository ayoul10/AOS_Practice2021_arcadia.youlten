#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <filesystem>
using namespace std;

#define OFFSET_FAT16 19
#define SIZE_FAT16 2
#define ELEMENTS_TO_READ_FAT16 1

//Todo: clean up
int volume_type(const char *fliename)
{
    //std::string file_information;
    size_t file_info;
    int flag =0;
    fseek(filename, OFFSET_FAT16, SEEK_SET);
    fread(file_info, SIZE_FAT16, ELEMENTS_TO_READ_FAT16, filename);
    flag=1;
    /*
    fats16
    bytes:
    offset 19, size 2
        If(BPB_FATSz16 != 0)    FATSz = BPB_FATSz16;


    */

    return flag;
}

int error_check(int argc, char *argv[])
{
    int flag=0;
    std::string command_wanted = "/info";
    //check files
    const char *filename = argv[2];
    std::ifstream in(filename);

    //TODO: Command line argument library?

    //check command line arguments
    if(argc < 3){
        cout << "Error! Too few arguments!" << endl;
        return flag = 1;
    }
    if (argc > 3)
    {
        cout << "Error! Too many arguments!" << endl;
        return flag = 1;
    }
    //check if we're entering the correct command
    if (command_wanted.compare(argv[1]) != 0)
    {
        cout << "Unknown Command." << endl;
        cout << "Try entering /info" << endl;
        return flag = 1;
    }
    //check validity of file 
    else{
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
            //check if we have an (EXT2 or FAT16)
            else if (volume_type(filename) == 0)
            {
                cout << "Error: File system is neither EXT2 nor FAT16" << endl;
                return flag =1; 
            }
            else{
                return flag;
            }
        }
    }
}

//TODO: Separate error checking into a different file for the project 

int main(int argc, char *argv[])
{

    if (error_check(argc, argv) == 1)
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