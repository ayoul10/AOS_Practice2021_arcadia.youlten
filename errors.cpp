#include "Errors.h"

int command_line_error_check(int argc, char *argv[])
{
    int flag = 0;
    std::string info = "/info";
    std::string find = "/find";

    if (argc < 3)
    {
        cout << "Error! Too few arguments!" << endl;
        return flag = 1;
    }
    //check if we're entering the correct command
    if ((info.compare(argv[1]) == 0) || (find.compare(argv[1]) == 0))
    {
        return flag =0;
    }
    else{

        cout << "Unknown Command." << endl;
        cout << "Try entering /info" << endl;
        return flag = 1;
    }
}

