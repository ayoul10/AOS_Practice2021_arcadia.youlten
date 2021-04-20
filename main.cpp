#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "FileManager.h"
#include "Errors.h"

int main(int argc, char *argv[])
{
    //Disk* disk_object = NULL;
    int filetype;
    if ((command_line_error_check(argc, argv) == 1) || fileTypeCheck(argv[2]) < 0)
    {
        cout << "Ending program due to errors" << endl;
    }
    else
    {
        showDiskInfo(argv[2]);
   
    }

    return 0;
}

