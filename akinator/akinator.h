#ifndef AKINATOR_INCLUDED
#define AKINATOR_INCLUDED

#include "../libs.h"
#include "../tree/tree.h"

//===================================================================================

void akinator_init      (akinator_tree* aktr, tree_node* tree);
void akinator_construct (akinator_tree* aktr, tree_node* tree);
void akinator_mode_1    (akinator_tree* aktr, tree_node* tree);
//===================================================================================

#endif