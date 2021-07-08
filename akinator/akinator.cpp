#include "../akinator/akinator.h"

//===================================================================================

void akinator_construct (akinator_tree* aktr, char* file_name, text* base_info)
{
    assert (aktr);
    assert (base_info);
    assert (file_name);

    input_inform (file_name, base_info);
    assert (base_info -> file_buffer);
    
 // это хуйня  placing_zeros (base_info);

    int idx = 0;

    create_akinator_tree (aktr, base_info, idx);
    akinator_init (aktr, aktr -> root);
}

//===================================================================================

void create_akinator_tree (akinator_tree* aktr, text* base_info, int idx)
{
    assert (aktr);
    assert (base_info);
    assert (base_info -> file_buffer);

    char* buffer = base_info -> file_buffer;

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

tree_node* create_akinator_node (char* buffer, int idx)
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

    char* word_ptr = create_word (buffer, idx);
    assert (word_ptr);

    if (buffer[idx] == '{')
    {
        cur_node -> right = create_akinator_node (buffer, idx);
    }// ТУТ МОЖЕТ СБИВАТЬСЯ ИНДЕКС ПОЖТОМУ ДВА РАЗА

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
    }        //У ифов сделать элсы
}

//===================================================================================

char* create_word (char* buffer, int idx)
{
    assert (buffer);

    char* word_ptr = buffer + idx;

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