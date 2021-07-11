#ifndef AKINATOR_INCLUDED
#define AKINATOR_INCLUDED

#include "../tree/tree.h"
#include "../libs/Onegin.h"
#include "../libs/include.h"

//===================================================================================

struct akinator_tree
{
    int   game_mode;
    text* base_info;
    tree_node* root;
};

//===================================================================================

void  akinator_construct   (akinator_tree* aktr, char* file_name);
void  akinator_destruct    (akinator_tree* aktr);
void  akinator_menu        (akinator_tree* aktr);
void  akinator_mode_1      (akinator_tree* aktr, tree_node* cur_node);
void  create_akinator_tree (akinator_tree* aktr, int idx);
char* create_word          (char* buffer, tree_node* cur_node, int &idx);

tree_node* create_akinator_node (char* buffer, int& idx);
tree_node* get_answer           (akinator_tree* aktr, tree_node* cur_node);

void akinator_graph (akinator_tree* aktr);
//===================================================================================

#endif