#include "akinator.h"
#include "../tree/tree.h"

int main ()
{
    tree_node tree      = {};  
    akinator_tree aktr  = {};
    
    akinator_construct (&aktr, &tree);

    tree_destuct (aktr.root);
    // tree_construct (&tree);
    return 0;
}