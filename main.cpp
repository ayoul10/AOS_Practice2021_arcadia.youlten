#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

//TODO: Separate error checking into a different file for the project 

int main(int argc, char *argv[])
{
    std::string command_wanted = "/info";
    //correct number of arguments
    //TODO: Command line argument library?
    if (argc < 2)
    {
        cout << "Error! please pass an operation (probably /info) and a disk volume of EXT2 or FAT16" << endl;
    }
    else if (argc > 2)
    {
        cout << "Error! Too many arguments!" << endl;
    }
    else if (command_wanted.compare(argv[0]) != 0)
    {
        cout << "Unknown Command." << endl;
        cout << "Try entering /info" << endl;
    }
    /*
    else if(){
      //TODO: Check to see if a file system is a EXT2 or FAT16  
      //TODO: Make sure file exsits
    }
    */
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