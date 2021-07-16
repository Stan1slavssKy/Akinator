#ifndef TREE_INCLUDED
#define TREE_INCLUDED

#include "../libs/include.h"
#include "../libs/Onegin.h"

//===================================================================================

struct tree_node 
{
    char*  data;
    struct tree_node *left;
    struct tree_node *right;
};

struct akinator_tree
{
    int   game_mode;
    int   answer;
    text* base_info;
    tree_node* root;
};

//===================================================================================

void node_destruct  (tree_node* cur_tree);
void tree_destruct  (tree_node* cur_node);

void  create_akinator_tree (akinator_tree* aktr, int idx);
void  akinator_graph       (akinator_tree* aktr);
void  node_graph           (tree_node* cur_node, FILE* grph_viz);
char* create_word          (char* buffer, tree_node* cur_node, int &idx);

tree_node* create_akinator_node (char* buffer, int& idx);

//===================================================================================

#endif