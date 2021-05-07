#include "../akinator/akinator.h"

//===================================================================================

tree_node* create_left (tree_node* cur_node, akinator_tree* aktr)
{
    assert (aktr);

    tree_node* left_ptr = (tree_node*) calloc (1, sizeof (tree_node));
    assert (left_ptr);

    if (cur_node == nullptr)
        aktr -> root = left_ptr;
    else 
        cur_node -> left = left_ptr;
    
    return left_ptr;
}

//===================================================================================

tree_node* create_right (tree_node* cur_node, akinator_tree* aktr)
{
    assert (aktr);

    tree_node* right_ptr = (tree_node*) calloc (1, sizeof (tree_node));
    assert (right_ptr);

    if (cur_node == nullptr)
        aktr -> root = right_ptr;
    else 
        cur_node -> right = right_ptr;

    return right_ptr;
}

//===================================================================================

void tree_dump ()
{

}

//===================================================================================

void print_node ()
{

}

//===================================================================================

void tree_fill_from_file ()
{

}

//===================================================================================

void node_destruct (tree_node* cur_node)
{
    if (cur_node == nullptr)
        return;

    node_destruct (cur_node -> left);
    node_destruct (cur_node -> right);

    free (cur_node);
}

//===================================================================================

void tree_destuct (tree_node* cur_node)
{
    if (cur_node == nullptr)
        return;

    node_destruct (cur_node -> left);
    node_destruct (cur_node -> right);

    cur_node -> left  = nullptr;
    cur_node -> right = nullptr;

    free (cur_node);
    cur_node = nullptr;
}

//===================================================================================