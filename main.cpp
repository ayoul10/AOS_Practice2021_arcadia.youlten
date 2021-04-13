#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "errors.h"
using namespace std;

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

