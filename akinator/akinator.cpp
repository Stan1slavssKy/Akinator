#include "../akinator/akinator.h"

//===================================================================================

void akinator_construct (akinator_tree* aktr, char* file_name)
{
    assert (aktr);
    assert (file_name);

    aktr -> base_info = (text*) calloc (1, sizeof (text*));
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

    print_hello ();

    aktr -> game_mode = handling_mod_input ();

    int game_mode = aktr -> game_mode;

    switch (game_mode)
    {
        case 1:
        {
            printf ("Вы выбрали режим отгадывания. Давайте начнем!\n");
            akinator_mode_1 (aktr, aktr -> root);
            
            akinator_menu   (aktr);
            break;
        }
            
        case 2:
        {
            printf ("Ты выбрал просмотр базы. Так вот же она:\n");
            const char string[] = "firefox GraphViz/base_dump.png";
            system (string);
            
            akinator_menu (aktr);
            break;
        }

        case 3:
        {
            printf ("Вы выбрали режим поиск свойств.\n"
            "Пожалуйста введите слово свойств которого вы хотите узнать.\n");
            akinator_mode_3 (aktr);

            akinator_menu (aktr);
            break;
        }

        case 4:
        {
            printf ("Вы выбрали режим сравнения слов."
            "Пожалуйста введите 2 слова, которые хотите сравнить:\n");
            akinator_mode_4 (aktr);

            akinator_menu (aktr);
            break;
        }

        case 5:
        {
            printf ("Ты захотел выйти. Пока...\n");
            return;
        }

        default:
        {
            printf ("Прости, но я не знаю такого режима игры.\n");
            break;
        }
    }
}

//===================================================================================

void print_hello ()
{
    printf ("Привет, я Акинатор. Пожалуйста выбери режим игры:\n"
    "1) режим отгадывания\n"
    "2) просмотреть базу\n"
    "3) режим поиска свойств\n"
    "4) режим сравнения слов\n"
    "5) выход\n");
}

//===================================================================================

int handling_mod_input ()
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
            printf ("Вы ввели слишком много символов попробуйте еще раз.\n");
            game_mode = -1;
        }
        else if (isdigit (*mode_buff))
        {
            game_mode = *mode_buff - CODE_ZERO;
        }
        else
        {
            printf ("Поожалуйста введите число, а не букву.\n");
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
            printf ("Я думаю это %s.\n", cur_node -> data);
                    
            tree_node* prev_cur_node = cur_node;
                    
            cur_node = get_answer (aktr, cur_node);
    
            if (cur_node == nullptr && aktr -> answer == YES)
            {
                printf ("Спасибо за игру. Пока!\n\n");
                return;
            }
            else if (cur_node == nullptr && aktr -> answer == NO)
            {
                printf ("Я не знаю, что ты загадал...\n");
                akinator_training (aktr, prev_cur_node);
                printf ("Спасибо за игру. Пока!\n\n");
                
                return;
            }
        }
    }
}

//===================================================================================

tree_node* get_answer (akinator_tree* aktr, tree_node* cur_node)
{
    assert (cur_node);

    int answ = handling_answer_input ();

    if (answ == NO)
    {
        aktr -> answer = answ;
        cur_node = cur_node -> left;
    }
    else if (answ == YES)
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

int handling_answer_input ()
{
    char* answer_buff = (char*) calloc (MAX_SYM, sizeof (char));
    assert (answer_buff);

    int ans_nmb = -1;
    
    while (ans_nmb == -1)
    {
        fgets (answer_buff, MAX_SYM, stdin);
        char* pointer = strchr (answer_buff, '\n');
        *pointer = '\0';

        if (!strcmp (answer_buff, "да"))
        { 
            ans_nmb = 1;
        }
        else if (!strcmp (answer_buff, "нет"))
        {
            ans_nmb = 0;
        }
        else 
        {
            printf ("Вам надо ввести \"да\" или \"нет\" без \"\".\n");
            ans_nmb = -1;
        }
    }

    free (answer_buff);
    return ans_nmb;
}

//===================================================================================

void akinator_training (akinator_tree* aktr, tree_node* cur_node)
{
    assert (aktr);
    assert (cur_node);

    cur_node -> right = (tree_node*) calloc (1, sizeof (tree_node));
    assert (cur_node -> right);

    cur_node -> left  = (tree_node*) calloc (1, sizeof (tree_node));
    assert (cur_node -> left);

    make_new_nodes (cur_node);
    
    akinator_graph       (aktr);
    create_akinator_base (aktr);
}

//===================================================================================

void make_new_nodes (tree_node* cur_node)
{
    printf ("Пожалуйста введите слово, которое вы загадали:\n");
    handling_training_input (cur_node -> right);
    
    int len = strlen (cur_node -> data);
    
    cur_node -> left -> data = (char*) calloc (len, sizeof (char));
    assert (cur_node -> data);

    strcpy (cur_node -> left -> data, cur_node -> data);

    printf ("Пожалуйста введите вопрос, который покажет разницу между "
    "%s и  %s?\n", cur_node -> right -> data, cur_node -> left -> data);
    handling_training_input (cur_node);
}

//===================================================================================

void handling_training_input (tree_node* cur_node)
{   
    char* answ = (char*) calloc (MAX_SYM, sizeof (char));
    assert (answ);

    fgets (answ, MAX_SYM, stdin);

    char* pointer = strchr (answ, '\n');
    *pointer = '\0';

    int len = pointer - answ;
    
    if (cur_node -> data == nullptr)
    {
        cur_node -> data = (char*) calloc (len, sizeof (char));
        assert (cur_node -> data);
    }

    strcpy (cur_node -> data, answ);
    free (answ);
}

//===================================================================================

void create_akinator_base (akinator_tree* aktr)
{
    assert (aktr);
    assert (aktr -> root);

    int cur_recursion_depth = 0;

    FILE* base = fopen ("base", "wb");
    assert (base);

    create_node_base (aktr -> root, base, cur_recursion_depth);
    
    fclose (base);
}

//===================================================================================

void create_node_base (tree_node* cur_node, FILE* base, int cur_recursion_depth)
{
    assert (base);

    if (cur_node -> right == nullptr && cur_node -> left == nullptr)
    {
        PLACING_TAB();
        fprintf (base, "{\n");
        PLACING_TAB();
        fprintf (base, "%s\n", cur_node -> data);
        PLACING_TAB()
        fprintf (base, "}\n");
        
        return;
    }

    PLACING_TAB();
    fprintf (base, "{\n");
    PLACING_TAB();
    fprintf (base, "%s\n", cur_node -> data);
    cur_recursion_depth++;

    create_node_base (cur_node -> right, base, cur_recursion_depth);
    create_node_base (cur_node -> left,  base, cur_recursion_depth);

    cur_recursion_depth--;
    PLACING_TAB()
    fprintf (base, "}\n");
}

//===================================================================================

void akinator_mode_3 (akinator_tree* aktr)
{
    assert (aktr);

    MAKE_WORD (word, len, end_ptr)

    tree_node* word_node = nullptr;

    word_node = tree_search (aktr -> root, word);
 
    if (word_node == nullptr)
    {
        printf ("Такого слова я не знаю. Спасибо за игру, пока!\n\n");
    }
    else 
    {
        print_properties (word_node);
    }

    free (word);
}

//===================================================================================

tree_node* tree_search (tree_node* cur_node, char* word)
{
    assert (word);
    
    if (!strcmp (cur_node -> data, word))
    {
        return cur_node;    
    }

    tree_node* out = nullptr;

    if (cur_node -> left  != nullptr) 
    {
        out = tree_search (cur_node -> left,  word);
    }
    if (cur_node -> right != nullptr && out == nullptr) 
    {
        out = tree_search (cur_node -> right, word);
    }

    return out;
}   

//===================================================================================

void print_properties (tree_node* cur_node)
{
    assert (cur_node);

    printf ("Свойства объекта %s:\n", cur_node -> data);

    while (cur_node -> prev_node != nullptr)
    {
        make_property (cur_node -> prev_node -> data);

        if (cur_node -> prev_node -> right == cur_node)
            printf ("\t-%s\n", cur_node -> prev_node -> data);

        else if (cur_node -> prev_node -> left == cur_node)
            printf ("\t-не %s\n", cur_node -> prev_node -> data);

        else
            printf ("Error %d\n", __LINE__);   
         
        cur_node = cur_node -> prev_node;
    }

    printf ("\n\n");
}

//===================================================================================

void make_property (char* word)
{
    char* pointer = strchr (word, '?');
   
    if (pointer != nullptr)
    {
        *pointer = '\0';
    }
}

//===================================================================================

void akinator_mode_4 (akinator_tree* aktr)
{
    assert (aktr);

    printf ("Первое слово: ");
    MAKE_WORD (fir_wrd, fir_len, fir_end)

    printf ("Второе слово: ");
    MAKE_WORD (sec_wrd, sec_len, sec_end)    
    printf ("\n");

    tree_node* fir_node = tree_search (aktr -> root, fir_wrd);
    tree_node* sec_node = tree_search (aktr -> root, sec_wrd);

    if (fir_node == nullptr && sec_node == nullptr)
    {
        printf ("Я не знаю этих слов. Спасибо за игру, пока!\n");
        return;
    }
    else if (fir_node == nullptr)
    {
        printf ("Я не знаю первого слова. Спасибо за игру, пока!\n");
        return;
    }
    else if (sec_node == nullptr)
    {
        printf ("Я не знаю второго слова. Спасибо за игру, пока!\n");
        return;
    }
        
    calling_stack (fir_node, sec_node, fir_wrd, sec_wrd);

    free (fir_wrd);
    free (sec_wrd);
}

//===================================================================================

void calling_stack (tree_node* fir_node, tree_node* sec_node, char* fir_wrd, char* sec_wrd)
{
    stack_constr (fir_stack, INIT_CAP);
    stack_constr (sec_stack, INIT_CAP);

    get_property_node_ptr (&fir_stack, fir_node);
    get_property_node_ptr (&sec_stack, sec_node);

    if (fir_stack.size == 0 || sec_stack.size == 0)
        printf ("Какого-то из слова нет!\n");

    search_common_properties (&fir_stack, &sec_stack, fir_wrd, sec_wrd);

    stack_destruct (&fir_stack);
    stack_destruct (&sec_stack);
}

//===================================================================================

void get_property_node_ptr (Stack_t* stack, tree_node* cur_node)
{
    assert (stack);

    stack_push (stack, (void*) cur_node);

    while (cur_node -> prev_node != nullptr)
    {
        if (cur_node -> prev_node -> right == cur_node || cur_node -> prev_node -> left == cur_node)
            stack_push (stack, (void*)cur_node -> prev_node);
        else 
            printf ("Error, %d\n", __LINE__);

        cur_node = cur_node -> prev_node;
    }
}

//===================================================================================

void search_common_properties (Stack_t* fir_stack, Stack_t* sec_stack, char* fir_word, char* sec_word)
{
    stack_pop (fir_stack);      
    stack_pop (sec_stack);  

    tree_node* fir_node = (tree_node*) stack_pop (fir_stack);      
    tree_node* sec_node = (tree_node*) stack_pop (sec_stack);
    
    printf ("Поиск схожих свойств для объектов %s и %s:\n", fir_word, sec_word);

    while (fir_stack -> size + 1 && sec_stack -> size + 1)
    {
        if (fir_node == sec_node)
        {  
            if (fir_node -> prev_node -> left == fir_node)
                printf ("\t-Не %s\n", fir_node -> prev_node -> data);
            else 
                printf ("\t-%s\n", fir_node -> prev_node -> data);
        }
        else if (fir_node -> prev_node -> left == fir_node)
        {
            printf ("\t-Есть отличие: %s %s, a %s не %s\n", sec_word, sec_node -> prev_node -> data, fir_word, fir_node -> prev_node -> data);    
            break;
        }
        else if (fir_node -> prev_node -> right == fir_node)
        {
            printf ("\t-Есть отличие: %s %s, a %s не %s\n", fir_word, fir_node -> prev_node -> data, sec_word, sec_node -> prev_node -> data);    
            break;
        }
        else    
            printf ("\t\t\tError %d\n", __LINE__);

        fir_node = (tree_node*) stack_pop (fir_stack); 
        sec_node = (tree_node*) stack_pop (sec_stack);
    }

    printf ("\n");
}

//===================================================================================

void akinator_destruct (akinator_tree* aktr)
{
    assert (aktr);
    assert (aktr -> root);
    assert (aktr -> base_info);
    assert ((aktr -> base_info) -> file_buffer);

    tree_destruct (aktr -> root);
    free ((aktr -> base_info) -> file_buffer);
    free (aktr -> base_info);
}

//===================================================================================
