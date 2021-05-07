#ifndef AKINATOR_INCLUDED
#define AKINATOR_INCLUDED

#include "../include.h"
#include "../tree/tree.h"
#include "../libs/Onegin.h"

//===================================================================================

void akinator_init      (akinator_tree* aktr, tree_node* cur_node);
void akinator_construct (akinator_tree* aktr, tree_node* cur_node, char* file_name, text* base_info);
void akinator_destruct  (akinator_tree* aktr, text* base_info);
void akinator_mode_1    (akinator_tree* aktr, tree_node* cur_code);
tree_node* get_answer   (akinator_tree* aktr, tree_node* cur_node);

void create_akinator_tree (akinator_tree* aktr, tree_node* cur_node, text* base_info, int idx);

//===================================================================================

#endif