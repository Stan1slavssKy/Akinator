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
            akinator_mode_1 (aktr, aktr -> root);
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
    char* mode_buff = (char*) calloc (MAX_SYM, sizeof (char));;
    assert (mode_buff);

    int game_mode = -1;

    while (game_mode == -1)
    {
        fgets (mode_buff, MAX_SYM, stdin);
        char* pointer = strchr (mode_buff, '\n');
        *pointer = '\0';

        if (pointer - mode_buff > 1)
        {
            printf ("Error, you entered too much symbols, please try again.\n");
            game_mode = -1;
        }
        else if (isdigit (*mode_buff))
        {
            game_mode = *mode_buff - CODE_ZERO;
        }
        else
        {
            printf ("Please enter a number, not a symbol.\n");
            game_mode = -1;  
        }
    }

    free (mode_buff);
    return game_mode;
}

//===================================================================================

void akinator_mode_1 (akinator_tree* aktr, tree_node* cur_node)
{
    assert (aktr);
    
    while (cur_node != nullptr)
    {
        printf ("%s\n", cur_node -> data);
        cur_node = get_answer (aktr, cur_node);

        if (cur_node -> left == nullptr && cur_node -> right == nullptr)
        {
            printf ("I think it is %s.\n", cur_node -> data);
            cur_node = get_answer (aktr, cur_node);
    
            if (cur_node == nullptr && aktr -> answer == 1)
            {
                printf ("Thanks for game. Good bye!\n");
                return;
            }
            else if (cur_node == nullptr && aktr -> answer == 0)
            {
                printf ("I don't know what are you thinkong about...\n");
                return;
            }
        }
    }
}

//===================================================================================

tree_node* get_answer (akinator_tree* aktr, tree_node* cur_node)
{
    assert (cur_node);

    int answ = processing_answer_input ();

    if (answ == 0)
    {
        aktr -> answer = answ;
        cur_node = cur_node -> left;
    }
    else if (answ == 1)
    {
        aktr -> answer = answ;
        cur_node = cur_node -> right;
    }
    else 
    {
        printf ("Error, %d", __LINE__);
        abort ();
    }

    return cur_node;
}

//===================================================================================

int processing_answer_input ()
{
    char* answer_buff = (char*) calloc (MAX_SYM, sizeof (char));
    assert (answer_buff);

    int ans_nmb = -1;
    
    while (ans_nmb == -1)
    {
        fgets (answer_buff, MAX_SYM, stdin);
        char* pointer = strchr(answer_buff, '\n');
        *pointer = '\0';

        if (pointer - answer_buff > 3)
        {
            printf ("You entered too much symbols, please try again. You need to write \"yes\" or \"no\" without \"\".\n");
            ans_nmb = -1;
        }

        if (!strcmp (answer_buff, "yes"))
        { 
            ans_nmb = 1;
        }
        else if (!strcmp (answer_buff, "no"))
        {
            ans_nmb = 0;
        }
        else 
        {
            printf ("You need to write \"yes\" or \"no\" without \"\".\n");
            ans_nmb = -1;
        }
    }

    free (answer_buff);
    return ans_nmb;
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
