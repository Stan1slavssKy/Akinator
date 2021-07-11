#ifndef TREE_INCLUDED
#define TREE_INCLUDED

#include "../libs/include.h"

//===================================================================================

struct tree_node 
{
    char*  data;
    struct tree_node *left;
    struct tree_node *right;
};

//===================================================================================

void node_destruct  (tree_node* cur_tree);
void tree_destuct   (tree_node* cur_tree);

//===================================================================================

#endif