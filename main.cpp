#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "FileManager.h"
#include "errors.h"

//#include "Fat16.h"
//#include "Ext2.h"
//#include "Disk.h"


int main(int argc, char *argv[])
{

    if ((command_line_error_check(argc, argv) == 1) || fileTypeCheck(argv[2]) < 0)
    {
        cout << "Ending program due to errors" << endl;
    }
    else
    {
        cout << "We're inside the program" << endl;
    }

    return 0;
}

