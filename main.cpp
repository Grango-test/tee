#include "mytee.h"

int main(int argc, char** argv)
{
    mytee teeObject;
    teeObject.parse_args(argc, argv);
    teeObject.std_input();
    teeObject.file_output();
    teeObject.std_output();
    return 0;
}

