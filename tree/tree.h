#ifndef TREE_INCLUDED
#define TREE_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

//===================================================================================

struct tree_node 
{
    char*  data             = nullptr;
    struct tree_node *left  = nullptr;
    struct tree_node *right = nullptr;
};

//===================================================================================


//===================================================================================

#include "akinator.h"

//===================================================================================

void tree_construct (tree_node* tree);
void node_destruct  (tree_node* object);
void tree_destuct   (tree_node* object, tree_node* tree, akinator* aktr);

tree_node* add_left_child (tree_node* object, tree_node* tree, akinator* aktr);
tree_node* add_left_child (tree_node* object, tree_node* tree, akinator* aktr);

//===================================================================================

#endif