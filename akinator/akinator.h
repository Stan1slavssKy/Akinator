#ifndef AKINATOR_INCLUDED
#define AKINATOR_INCLUDED

#include "../tree/tree.h"

//===================================================================================

const int MAX_SYM   = 100;
const int CODE_ZERO = 48;

//===================================================================================

enum answer
{
    NO  = 0,
    YES = 1
};

//===================================================================================

void  akinator_construct   (akinator_tree* aktr, char* file_name);
void  akinator_destruct    (akinator_tree* aktr);
void  akinator_menu        (akinator_tree* aktr);
void  print_hello          ();
void  akinator_training    (akinator_tree* aktr, tree_node* cur_node);
void  akinator_mode_1      (akinator_tree* aktr, tree_node* cur_node);

int   handling_mod_input      ();
int   handling_answer_input   ();
void  handling_training_input (tree_node* cur_node);

tree_node* get_answer (akinator_tree* aktr, tree_node* cur_node);

//===================================================================================

#endif