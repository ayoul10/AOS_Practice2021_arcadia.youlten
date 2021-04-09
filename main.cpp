#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "errors.h"
using namespace std;

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