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
            akinator_mode_1 (aktr -> root);
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
    char* mode_buf = (char*) calloc (MAX_SYM, sizeof (char));;
    assert (mode_buf);

    int   game_mode = 0;
    int   nmb_symb  = 0;
    char* pointer   = mode_buf;

    while ((*pointer = getchar ()) != '\n' && (nmb_symb < MAX_SYM))
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

void akinator_mode_1 (tree_node* cur_node)
{
    assert (cur_node);

    while (true)
    {
        if (cur_node -> left == nullptr && cur_node -> right == nullptr)
        {
            printf ("I don't know what you're thinking.\n");
            break;
        }

        cur_node = get_answer (cur_node);
        if (cur_node == nullptr) return;
    }
}

//===================================================================================

tree_node* get_answer (tree_node* cur_node)
{
    assert (cur_node);

    int nmb_symbs = processing_answer_input ();

    printf ("NMB_SYMBOLS = %d\n", nmb_symbs);

    if (nmb_symbs == 2)
    {
        printf ("\t\t\t\tNo\n");
        return nullptr;
    }
    else if (nmb_symbs == 3)
    {
        printf ("\t\t\t\tYes\n");
        return nullptr;
    }
    else 
    {
        printf ("Error, %d", __LINE__);
        return nullptr;
    }

    return cur_node;
}

//===================================================================================

int processing_answer_input ()
{
    char* answer_buff = (char*) calloc (MAX_SYM, sizeof (char));
    assert (answer_buff);

    int   nmb_symb = 0;
    char* pointer  = answer_buff;

    while ((*pointer = getchar()) != '\n' && (nmb_symb < MAX_SYM))
    {
        pointer++;
        nmb_symb++;   
    }
    
    if (nmb_symb > 3)
    {
        printf ("You entered too much symbols, please try again. You need to write \"yes\" or \"no\" without \"\".\n");
        free (answer_buff);
        int x = processing_answer_input ();
        return x;
    }
    else if (nmb_symb == strlen ("yes"))                                     
    {                                                                        
        answer_buff = (char*) realloc (answer_buff, NMB_S_YES);          
        assert (answer_buff);                                         
        
        if (!strcmp (answer_buff, "yes"))                                    
        {                                          
            free (answer_buff);                                              
            return nmb_symb;                                                 
        }                                                                    
        else                                                                 
        {                                                                    
            printf ("You need to write \"yes\" or \"no\" without \"\".\n");  
            free (answer_buff);                                              
            int x = processing_answer_input ();                              
            return x;                                                        
        }
    }                               

    else if (nmb_symb == strlen ("no"))                                     
    {                                                                        
        answer_buff = (char*) realloc (answer_buff, NMB_S_NO);          
        assert (answer_buff);                                                                    
        
        if (!strcmp (answer_buff, "no"))                                    
        {                                                                                                                                 
            free (answer_buff);                                              
            return nmb_symb;                                                 
        }                                                                    
        else                                                                 
        {                                                                    
            printf ("You need to write \"yes\" or \"no\" without \"\".\n");  
            free (answer_buff);                                              
            int x = processing_answer_input ();                              
            return x;                                                        
        }                                                                        
    }
    else
    {
        printf ("You need to write \"yes\" or \"no\" without \"\".\n");
        free (answer_buff);
        int x = processing_answer_input ();
        return x;    
    }

    free (answer_buff);
    return -1;
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
