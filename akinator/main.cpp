#include "akinator.h"
#include "../tree/tree.h"

int main (int argc, char** argv)
{

    setlocale (LC_ALL, "Rus");

    akinator_tree aktr = {};

    char* file_name = console_input (argc, argv);
    assert (file_name);

    akinator_construct (&aktr, file_name);
    akinator_destruct  (&aktr);

    return 0;
}   