#ifndef AKINATOR_INCLUDED
#define AKINATOR_INCLUDED

#include "../tree/tree.h"
#include "../libs/protection.h"

//===================================================================================

#define PLACING_TAB()                                   \
    fprintf (base, "%*s", cur_recursion_depth * 8, ""); \

//===================================================================================

#define MAKE_WORD(word_name, length, end_ptr)                         \
    char* word_name = (char*) calloc (MAX_SYM, sizeof (char));        \
    assert (word_name);                                               \
                                                                      \
    fgets (word_name, MAX_SYM, stdin);                                \
    char* end_ptr = strchr (word_name, '\n');                         \
    *end_ptr = '\0';                                                  \
                                                                      \
    int length = end_ptr - word_name;                                 \
                                                                      \
    word_name = (char*) realloc (word_name, length * sizeof (char));  \
    assert (word_name);                                               \

//===================================================================================

const int MAX_SYM   = 100;
const int CODE_ZERO = 48;
const int INIT_CAP  = 20;

const char BASE_OPEN[] = "firefox GraphViz/base_dump.png";

//===================================================================================

enum answer
{
    NO  = 0,
    YES = 1
};

//===================================================================================

enum game_mode
{
    GUESSING_MODE = 1,
    BASE_MODE        ,
    PROPERTIES_MODE  ,
    COMPARASION_MODE ,
    EXIT_MODE        
};

//===================================================================================

void  akinator_construct   (akinator_tree* aktr, char* file_name);
void  akinator_destruct    (akinator_tree* aktr);
void  akinator_menu        (akinator_tree* aktr);
void  print_mode           ();
void  akinator_training    (akinator_tree* aktr, tree_node* cur_node);

void  guess_mode           (akinator_tree* aktr, tree_node* cur_node);
void  properties_mode      (akinator_tree* aktr);
void  comparison_mode      (akinator_tree* aktr);

int   handling_mod_input      ();
int   handling_answer_input   ();
void  handling_training_input (tree_node* cur_node);

void  create_akinator_base (akinator_tree* aktr);
void  create_node_base     (tree_node* cur_node, FILE* base, int cur_recursion_depth);
void  make_new_nodes       (tree_node* cur_node);
void  print_properties     (tree_node* cur_node);
void  make_property        (char* word);

void  get_property_node_ptr    (Stack_t* stack, tree_node* cur_node);
void  search_common_properties (Stack_t* fir_stack, Stack_t* sec_stack, char* fir_word, char* sec_word);
void  calling_stack            (tree_node* fir_node, tree_node* sec_node, char* fir_wrd, char* sec_wrd);

tree_node* tree_search    (tree_node* cur_node, char* word);
tree_node* get_answer     (akinator_tree* aktr, tree_node* cur_node);

//===================================================================================

#endif