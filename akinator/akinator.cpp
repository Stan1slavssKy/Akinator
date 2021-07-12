#include "../akinator/akinator.h"

//===================================================================================

void akinator_construct (akinator_tree* aktr, char* file_name)
{
    assert (aktr);
    assert (file_name);

    aktr -> base_info = (text*) calloc (1, sizeof(text*));
    assert (aktr -> base_info);

    input_inform (file_name, aktr -> base_info);
    assert ((aktr -> base_info) -> file_buffer);

    int idx = 0;

    create_akinator_tree (aktr, idx);
    akinator_graph (aktr);
  //  akinator_menu (aktr);
}

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

void akinator_menu (akinator_tree* aktr)
{
    assert (aktr);
    assert (aktr -> root);

    printf ("Hi, I'm Akinator, please choise game mode:\n\t\t\t  1) guessing game\n");
    scanf  ("%d", &(aktr -> game_mode));
    
    int game_mode = aktr -> game_mode;

    switch (game_mode)
    {
        case 1:
            printf ("You choice guessing game, lets start!\n");
            akinator_mode_1 (aktr, aktr -> root);
            break;
        
        default:
            printf ("Sorry I don't know this mode\n");
            break;
    }
}

//===================================================================================

void akinator_mode_1 (akinator_tree* aktr, tree_node* cur_node)
{
    assert (aktr);
    assert (aktr -> root);
    assert (cur_node);

    while (true)
    {
        if (cur_node -> left == nullptr && cur_node -> right == nullptr)
        {
            printf ("I don't know what you're thinking.\n");
            break;
        }

        printf ("Is it %s?\n", cur_node -> data);
        cur_node = get_answer (aktr, cur_node);
    }
}

//===================================================================================

tree_node* get_answer (akinator_tree* aktr, tree_node* cur_node)
{
    assert (aktr);
    assert (aktr -> root);
    assert (cur_node);

    char answer[3] = {};

    scanf ("%s", answer);

    if (!strcmp (answer, "yes"))
        cur_node = cur_node -> right;  
    
    else if (!strcmp (answer, "no"))
        cur_node = cur_node -> left;  

    else 
        printf ("Sorry you didn't enter yes or no.\n");

    return cur_node;
}

//===================================================================================

void akinator_graph (akinator_tree* aktr)
{
    assert (aktr);
    assert (aktr -> root);

    FILE* grph_viz = fopen ("GraphViz/base_dump.dot", "wb");
    assert (grph_viz);
    
    fprintf (grph_viz, "digraph Akinator {\n");
    fprintf (grph_viz, "node [shape=\"circle\"]\n");

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

        fprintf (grph_viz, "\"%s\" -> \"%s\";\n", cur_data, left_data);
        fprintf (grph_viz, "\"%s\" -> \"%s\";\n", cur_data, right_data);

        node_graph (cur_node -> right, grph_viz);
        node_graph (cur_node -> left,  grph_viz);
    }
}

//===================================================================================

void akinator_destruct (akinator_tree* aktr)
{
    assert (aktr);
    assert (aktr -> root);
    assert (aktr -> base_info);
    assert ((aktr -> base_info) -> file_buffer);

    tree_destuct (aktr -> root);
    free ((aktr -> base_info) -> file_buffer);
    free (aktr -> base_info);
}

//===================================================================================
