#include "../akinator/akinator.h"

//===================================================================================

void akinator_construct (akinator_tree* aktr, tree_node* tree)
{
    add_left_child (nullptr, tree, aktr);
    
    add_left_child  (aktr -> root, tree, aktr);
    add_right_child (aktr -> root, tree, aktr);
    
    aktr -> root -> data          = "Animal";
    aktr -> root -> left  -> data = "Human";
    aktr -> root -> right -> data = "Cat";
    
    akinator_init (aktr, tree);
}

//===================================================================================

void akinator_init (akinator_tree* aktr, tree_node* tree)
{
    printf ("Hi, I'm Akinator, please choise game mode:\n\t\t\t  1) guessing game\n");
    scanf  ("%d", &(aktr -> game_mode));

    int game_mode = aktr -> game_mode;

    switch (game_mode)
    {
        case 1:
            printf ("You choice guessing game, lets start!\n");
            akinator_mode_1 (aktr, tree);
            break;
        
        default:
            printf ("Sorry I don't know this mode\n");
            break;
    }
}

//===================================================================================

void akinator_mode_1 (akinator_tree* aktr, tree_node* tree)
{
    printf ("Is it %s?\n", aktr -> root -> data);
   
    char answer[3] = {};

    scanf ("%s", answer);

    if (!strcmp (answer, "yes"))
    {
        printf ("Is it %s?\n", aktr -> root -> right -> data);    
    }
    
    else if (!strcmp (answer, "no"))
    {
        printf ("Is it %s?\n", aktr -> root -> left  -> data);    
    }

    else 
        printf ("Sorry you didn't enter yes or no.\n");
}

//===================================================================================

void get_answer ()
{

}