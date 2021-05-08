#include "../akinator/akinator.h"

//===================================================================================

void akinator_construct (akinator_tree* aktr, tree_node* cur_node, char* file_name, text* base_info)
{
    assert (aktr);
    assert (base_info);
    assert (file_name);

    input_inform (file_name, base_info);
    assert (base_info -> file_buffer);
    
    placing_zeros (base_info);
    
    base_analize  (aktr, cur_node, base_info);
   // akinator_init (aktr, cur_node);
}

//===================================================================================

void base_analize (akinator_tree* aktr, tree_node* cur_node, text* base_info)
{
    assert (aktr);
    assert (base_info);
    assert (base_info -> file_buffer);
    
    char* buffer = base_info -> file_buffer;
    int   idx    = 0;

    while (buffer[idx] != '{')
        idx++;
    
    idx++;
    
    while (isspace(buffer[idx]))
        idx++;

    if (aktr -> root == nullptr)
    {
        cur_node = create_left (nullptr, aktr);    
        assert (cur_node);

        cur_node -> data = buffer + idx;
        printf ("slovo = %s\n", cur_node ->data);
    }

    while ((buffer[idx] != '{') && (buffer[idx] != '}'))
        idx++;
    
    if (buffer[idx] == '}')
        return;

    create_left  (cur_node, aktr);
    create_right (cur_node, aktr);
    
    create_akinator_tree (aktr, cur_node -> right, base_info, idx);
    create_akinator_tree (aktr, cur_node -> left,  base_info, idx);
}

//===================================================================================

void create_akinator_tree (akinator_tree* aktr, tree_node* cur_node, text* base_info, int idx)
{
    assert (aktr);
    assert (base_info);
    assert (base_info -> file_buffer);

    char* buffer = base_info -> file_buffer;


    while (buffer[idx] != '{')
        idx++;
    
    if (buffer[idx] == '{')
    {
        idx++;

        while (isspace(buffer[idx]))
            idx++;

        cur_node -> data = buffer + idx;

        create_left  (cur_node, aktr);
        create_right (cur_node, aktr);   
    }

    while (buffer[idx] != '{' && buffer[idx] != '}')
        idx++;
    
    if (buffer[idx] == '}')
        return;

    create_akinator_tree (aktr, cur_node -> right, base_info, idx);
    create_akinator_tree (aktr, cur_node -> left,  base_info, idx);
}

//===================================================================================

void akinator_init (akinator_tree* aktr, tree_node* cur_node)
{
    assert (aktr);
    assert (aktr -> root);
    assert (cur_node);

    printf ("Hi, I'm Akinator, please choise game mode:\n\t\t\t  1) guessing game\n");
    scanf  ("%d", &(aktr -> game_mode));

    int game_mode = aktr -> game_mode;

    switch (game_mode)
    {
        case 1:
            printf ("You choice guessing game, lets start!\n");
            akinator_mode_1 (aktr, cur_node);
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

void akinator_destruct  (akinator_tree* aktr, text* base_info)
{
    assert (aktr);
    assert (aktr -> root);
    assert (base_info);
    assert (base_info -> file_buffer);

    tree_destuct (aktr -> root);
    free (base_info -> file_buffer);
}

//===================================================================================
