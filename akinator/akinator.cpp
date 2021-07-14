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
    akinator_menu  (aktr);
}

//===================================================================================

void akinator_menu (akinator_tree* aktr)
{
    assert (aktr);
    assert (aktr -> root);

    printf ("Hi, I'm Akinator, please choise game mode:\n"
    "1) guessing game\n"
    "2) check base\n"
    "3) exit\n");

    aktr -> game_mode = processing_mod_input ();

    int game_mode = aktr -> game_mode;

    switch (game_mode)
    {
        case 1:
        {
            printf ("You choice guessing game, lets start!\n");
           // akinator_mode_1 (aktr, aktr -> root);
            break;
        }
            
        case 2:
        {
            printf ("You have chosen to view the database. Here it is:\n");
            const char string[] = "firefox GraphViz/base_dump.png";
            system (string);
            break;
        }

        case 3:
        {
            printf ("You want exit. Bye...\n");
            return;
        }

        default:
        {
            printf ("Sorry I don't know this mode\n");
            break;
        }
    }
}

//===================================================================================

int processing_mod_input ()
{
    char* mode_buf = (char*) calloc (MAX_MODE_SYM, sizeof (char));;
    assert (mode_buf);

    int   game_mode = 0;
    int   nmb_symb  = 0;
    char* pointer   = mode_buf;

    while ((*pointer = getchar ()) != '\n' && (nmb_symb < MAX_MODE_SYM))
    {
        pointer++;
        nmb_symb++;    
    }

    if (nmb_symb > 1)
    {
        printf ("Error, you entered too much symbols, please try again.\n");
        free (mode_buf);

        game_mode = processing_mod_input ();
        return game_mode; 
    }
    else if (isdigit (*mode_buf))
    {
        game_mode = *mode_buf - CODE_ZERO;
        free (mode_buf);

        return game_mode;
    }
    else
    {
        printf ("Please enter a number, not a symbol.\n");
        free (mode_buf);

        game_mode = processing_mod_input ();
        return game_mode;  
    }

    return -1;
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