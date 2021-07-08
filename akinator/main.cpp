#include "akinator.h"
#include "../tree/tree.h"

int main (int argc, char** argv)
{
    text          base_info = {};
    akinator_tree aktr      = {};

    char* file_name = console_input (argc, argv);
    assert (file_name);

    akinator_construct (&aktr, file_name, &base_info);
    akinator_destruct  (&aktr, &base_info);

    return 0;
}   