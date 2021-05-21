#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "FileManager.h"
#include "Errors.h"

#define INFO "/info"
#define FIND "/find"
#define DELETE "/delete"

int main(int argc, char *argv[])
{
    if ((command_line_error_check(argc, argv) == 1) )
    {
        cout << "Ending program due to errors" << endl;
    }
    else
    {
        if (strcmp(argv[1], INFO) == 0){
            showDiskInfo(argv[2]);
        }
        else if (strcmp(argv[1], FIND) == 0){
            //when running FAT16, a message that displays the root size appears. I don't know where this message is coming from.
            findFileonDisk(argv[2], argv[3]);

        }
        else if (strcmp(argv[1], DELETE) == 0){
            cout << "Not Implemented Yet" << endl;
        }
    }

    return 0;
}

