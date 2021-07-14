#ifndef AKINATOR_INCLUDED
#define AKINATOR_INCLUDED

#include "../tree/tree.h"

#define MAX_MODE_SYM 10
#define CODE_ZERO 48

//===================================================================================

void  akinator_construct   (akinator_tree* aktr, char* file_name);
void  akinator_destruct    (akinator_tree* aktr);
void  akinator_menu        (akinator_tree* aktr);
void  akinator_mode_1      (akinator_tree* aktr, tree_node* cur_node);
int   processing_mod_input ();

tree_node* get_answer           (akinator_tree* aktr, tree_node* cur_node);

//===================================================================================

#endif