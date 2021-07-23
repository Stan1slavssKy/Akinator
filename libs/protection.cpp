#include "protection.h"

void stack_null (Stack_t* stack)
{
    if (stack == nullptr)
    {
        printf ("STACK IS NULL!\n");
    }
}

//-------------------------------------------------------------------------------------------------------------

void poison_fill_in (Stack_t* stack, size_t beg, size_t end)
{
    for (size_t i = beg; i < end; i++)
    {
        *(stack -> data + i) = POISON_XXX;
    }
}

//-------------------------------------------------------------------------------------------------------------

void placing_canaries (Stack_t* stack, void* memory)
{
    stack_null (stack);
    
    canary_t* canary_array_left = (canary_t*) memory;
    *canary_array_left = Canary;
        
    stack -> data = (elem_t*) (canary_array_left + 1); //кладёт указатель в структуру 
                        
    canary_t* canary_array_right = (canary_t*) (stack -> data + stack -> capacity);
    *canary_array_right = Canary;  
}

//-------------------------------------------------------------------------------------------------------------

const char* error_detect (Stack_t* stack)
{
    assert (stack);

    switch (stack -> error)
    {
        case 0:
            return "STACK_IS_OK";

        error_case (MEMORY_OUT);
        error_case (NEGATIVE_SIZE);
        error_case (NEGATIVE_CAPACITY);
        error_case (WRONG_CANARY_STRUCT_LEFT);
        error_case (WRONG_CANARY_STRUCT_RIGHT);
        error_case (WRONG_CANARY_ARRAY_LEFT);
        error_case (WRONG_CANARY_ARRAY_RIGHT);
        error_case (NULL_DATA);
        error_case (WRONG_HASH);

        default:
            return "UNNOWN_ERROR!";
    }
}  

//-------------------------------------------------------------------------------------------------------------

int stack_ok (Stack_t* stack)
{
    if (stack -> error != 0)
    {
        return stack -> error;
    }

    else
    {
        if (stack -> capacity != 0 && stack -> data == nullptr)
        {
            stack -> error = NULL_DATA;
            return NULL_DATA;
        }
        
        if (stack -> data == nullptr)
        {
            stack -> error = NULL_DATA;
            return NULL_DATA;
        }
        
        if (stack -> size < 0)
        {
            stack -> error = NEGATIVE_SIZE;
        }

        if (stack -> left_struct_canary != Canary)
        {
            stack -> error = WRONG_CANARY_STRUCT_LEFT;
            return WRONG_CANARY_STRUCT_LEFT;
        }

        if (stack -> right_struct_canary != Canary)
        {
            stack -> error = WRONG_CANARY_STRUCT_RIGHT;
            return WRONG_CANARY_STRUCT_RIGHT;
        }

        if (*((canary_t*)(stack -> data) - 1) != Canary)
        {
            stack -> error = WRONG_CANARY_ARRAY_LEFT;
            return WRONG_CANARY_ARRAY_LEFT;
        }

        if (*((canary_t*)(stack -> data + stack -> capacity)) != Canary)
        {    
            stack -> error = WRONG_CANARY_ARRAY_RIGHT;
            return WRONG_CANARY_ARRAY_RIGHT;
        }

        if (stack -> hash != stack_hash (stack))
        {
            stack -> error = WRONG_HASH;
            printf ("Stack hacked!\n");
           
            return WRONG_HASH;
        }
    }

    return 0;
}

//-------------------------------------------------------------------------------------------------------------

void stack_dump (Stack_t* stack)
{
    const char* text_of_error = error_detect (stack);

    canary_t* left_arr_can  = (canary_t*)(stack -> data) - 1;
    canary_t* right_arr_can = (canary_t*)(stack -> data + stack -> capacity);

    printf ("===================STACK DUMP===================\n");
   
    #ifdef PROTECTION
        if (stack -> error != 0)
            printf ("Error №%d found in the stack: %s\n", stack -> error, text_of_error);
        else
            printf ("\t\t  Stack is OK!\n");
    #endif 

    printf ("Struct left  canary[%p] = %lld\n", &stack -> left_struct_canary, stack -> left_struct_canary);
    printf ("Stack  size                         = %ld\n", stack -> size) ;
    printf ("Stack  capacity                     = %ld\n", stack -> capacity);
    printf ("Array  left  canary[%p] = %lld\n", left_arr_can, *left_arr_can);
    printf ("Stack  data        [%p]\n", stack -> data);
    printf ("Array  right canary[%p] = %lld\n", right_arr_can, *right_arr_can);
    printf ("Struct right canary[%p] = %lld\n", &stack -> right_struct_canary, stack -> right_struct_canary);

    print_array (stack);
    printf ("================================================\n");
}

//-------------------------------------------------------------------------------------------------------------

void print_array (Stack_t* stack)
{
    #ifdef DOUBLE_TYPE
        for (int i = 0; i < stack -> capacity; i++) 
            printf ("\t\t[%d]: %f\n", i, *(stack -> data + i)); 
    #else
        #ifdef INT_TYPE
            for (int i = 0; i < stack -> capacity; i++) 
                printf ("\t\t[%d]: %d\n", i, *(stack -> data + i));
        #endif
    #endif

    #ifdef POINTER_TYPE
        for (int i = 0; i < stack -> capacity; i++) 
                printf ("\t\t[%d]: %p\n", i, *(stack -> data + i)); 
    #endif
}

//-------------------------------------------------------------------------------------------------------------

size_t stack_hash (Stack_t* stack)
{
    
}