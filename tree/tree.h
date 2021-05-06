#ifndef TREE_INCLUDED
#define TREE_INCLUDED

#include "../libs.h"

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

void tree_construct (tree_node* tree);
void node_destruct  (tree_node* current_node);
void tree_destuct   (tree_node* current_node);

tree_node* add_left_child  (tree_node* current_node, tree_node* tree, akinator_tree* aktr);
tree_node* add_right_child (tree_node* current_node, tree_node* tree, akinator_tree* aktr);

//===================================================================================

#endif