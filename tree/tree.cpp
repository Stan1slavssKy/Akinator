#include "tree.h"

//===================================================================================

void create_akinator_tree (akinator_tree* aktr, int idx)
{
    assert (aktr);
    assert (aktr -> base_info);
    assert ((aktr -> base_info) -> file_buffer);

    char* buffer = (aktr -> base_info) -> file_buffer;

    if (aktr -> root == nullptr) 
    {
        while (isspace(buffer[idx])) idx++;

        if (buffer[idx] == '{')
        {
            aktr -> root = create_akinator_node (buffer, idx);    
        }
        else 
        {
            printf ("Error, %d", __LINE__);
        }
    }

    else
        printf ("Error, second create of aktr tree, %d", __LINE__);
}   

//===================================================================================

tree_node* create_akinator_node (char* buffer, int& idx)
{
    assert (buffer);

    if (buffer[idx] == '{')
    {    
        idx++;
        
        while (isspace(buffer[idx]))
            idx++;
    }
    else 
    {
        printf ("Error, %d", __LINE__);
    }

    if (buffer[idx] == '}')
    {
        return nullptr;
    }

    tree_node* cur_node = (tree_node*) calloc (1, sizeof (tree_node));
    assert (cur_node);

    char* word_ptr = create_word (buffer, cur_node, idx);
    assert (word_ptr);

    if (buffer[idx] == '{')
    {
        cur_node -> right = create_akinator_node (buffer, idx);
    }

    while (isspace(buffer[idx]))
        idx++;

    if (buffer[idx] == '{')
    {
        cur_node -> left  = create_akinator_node (buffer, idx);
    }

    while (isspace(buffer[idx]))
        idx++;

    
    if (buffer[idx] == '}')
    {
        idx++;
        return cur_node;
    }   
}

//===================================================================================

char* create_word (char* buffer, tree_node* cur_node, int &idx)
{
    assert (buffer);

    char* word_ptr = buffer + idx;
   
    cur_node -> data = word_ptr;

    while (true)
    {
        if (buffer[idx] == '\n')
        {   
            buffer[idx] =  '\0';
            idx++;
            break;
        }
        idx++;
    }

    printf ("slovo = %s\n", word_ptr);
    
    while (isspace(buffer[idx]))
        idx++;    

    return word_ptr;      
}

//===================================================================================

void akinator_graph (akinator_tree* aktr)
{
    assert (aktr);
    assert (aktr -> root);

    FILE* grph_viz = fopen ("GraphViz/base_dump.dot", "wb");
    assert (grph_viz);
    
    fprintf (grph_viz, "digraph Akinator \n{\n");
    fprintf (grph_viz, "\t\tnode [shape = \"circle\", color = \"darkgreen\", fontcolor = \"purple\"];\n");
    fprintf (grph_viz, "\t\tedge [color = \"darkgreen\"];\n\n");
    
    node_graph (aktr -> root, grph_viz);

    fprintf (grph_viz, "}");    

    fclose  (grph_viz);

    system ("dot -Tpng GraphViz/base_dump.dot -o GraphViz/base_dump.png");
}

//===================================================================================

void node_graph (tree_node* cur_node, FILE* grph_viz)
{  
    assert (cur_node);
    assert (grph_viz);

    char* cur_data = cur_node -> data;

    if (cur_node -> right != nullptr && cur_node -> left != nullptr)
    {
        char* left_data  = cur_node -> left  -> data;
        char* right_data = cur_node -> right -> data;

        fprintf (grph_viz, "\t\t\"%s\" -> \"%s\"[label = \"No\"];\n",  cur_data, left_data);
        fprintf (grph_viz, "\t\t\"%s\" -> \"%s\"[label = \"Yes\"];\n", cur_data, right_data);

        node_graph (cur_node -> right, grph_viz);
        node_graph (cur_node -> left,  grph_viz);
    }
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