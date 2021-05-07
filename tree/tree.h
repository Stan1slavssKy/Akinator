#ifndef TREE_INCLUDED
#define TREE_INCLUDED

#include "../include.h"

//===================================================================================

struct tree_node 
{
    char*  data             = nullptr;
    struct tree_node *left  = nullptr;
    struct tree_node *right = nullptr;
};

struct akinator_tree
{
    tree_node* root = nullptr;
    int game_mode   = 0;
};

//===================================================================================

void tree_construct (tree_node* cur_tree);
void node_destruct  (tree_node* cur_tree);
void tree_destuct   (tree_node* cur_tree);

tree_node* create_left  (tree_node* cur_tree, akinator_tree* aktr);
tree_node* create_right (tree_node* cur_tree, akinator_tree* aktr);

//===================================================================================

#endif