#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "FileManager.h"
#include "Errors.h"
/*
#include "Fat16.h"
#include "Ext2.h"
#include "Disk.h"
*/

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
        cout << "We're inside the program" << endl;

        //filetype = fileTypeCheck(argv[2]);

        //showDiskInfo(filetype, argv[2]);
        //disk_object = createObjectFromFile(filetype);
                
    }

    return 0;
}

