#include "Errors.h"

int command_line_error_check(int argc, char *argv[])
{
    int flag = 0;
    std::string command_wanted = "/info";

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
}