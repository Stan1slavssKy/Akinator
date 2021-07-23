#include "protection.h"

Stack_t* stack_construct (Stack_t* stack, long capacity)
{   
    stack_null (stack);

    if (capacity == 0)
    {
        stack -> capacity = (size_t) capacity;
        stack -> size = 0;
        stack -> data = nullptr;
        stack -> left_struct_canary  = Canary;
        stack -> right_struct_canary = Canary;

        stack_realloc (stack);
    }

    else if (capacity > 0)
    {
        stack -> capacity = (size_t) capacity;
        stack -> size = 0;
        stack -> data = nullptr;
        stack -> left_struct_canary  = Canary;
        stack -> right_struct_canary = Canary;
        
        #ifdef PROTECTION 
            void* memory = calloc (1, (stack -> capacity) * sizeof (elem_t) + 2 * sizeof (canary_t));
            
            if (memory == nullptr)
            {
                stack -> error = MEMORY_OUT;
                assert_ok (stack);
            }

            placing_canaries (stack, memory);
            poison_fill_in   (stack, stack -> size, stack -> capacity);

            stack -> hash = stack_hash (stack);
        #else 
            stack -> data = (elem_t*) calloc (1, (stack -> capacity) * sizeof (elem_t));
        #endif

        assert_ok (stack);
    }

    else if (capacity < 0)
    {
        stack -> error = NEGATIVE_CAPACITY;
        assert_ok (stack);
    }

    return stack;
}

//-----------------------------------------------------------------------------------------

void stack_realloc (Stack_t* stack) 
{
    stack_null (stack);

    if (stack -> capacity == 0)
    {
        stack -> capacity = INITIAL_CAPACITY;

        #ifdef PROTECTION 
            void* memory = calloc (1, stack -> capacity * sizeof (elem_t) + 2 * sizeof (canary_t));

            if (memory == nullptr)
            {
                stack -> error = MEMORY_OUT;
                assert_ok (stack);
            }

            placing_canaries (stack, memory);
            poison_fill_in   (stack, stack -> size, stack -> capacity);

            stack -> hash = stack_hash (stack);
        #else
            stack -> data = (elem_t*) calloc (1, stack -> capacity * sizeof (elem_t));
        #endif 

        assert_ok (stack);
    }

    else if (stack -> capacity == stack -> size)
    {
        size_t old_capacity = stack -> capacity;
        
        #ifdef PROTECTION 
            void* memory = realloc ((canary_t*)(stack -> data) - 1, (stack -> capacity *= X_CAPACITY) * sizeof (elem_t) + 2 * sizeof (canary_t));

            if (memory == nullptr)
            {
                stack -> error = MEMORY_OUT;
                assert_ok (stack);
            }

            placing_canaries (stack, memory);
            poison_fill_in (stack, old_capacity, stack -> capacity);

            stack -> hash = stack_hash (stack);
        #else 
            stack -> data = (elem_t*) realloc (stack -> data, (stack -> capacity *= X_CAPACITY) * sizeof (elem_t));
        #endif
        
        assert_ok (stack);
    }
}

//-----------------------------------------------------------------------------------------

void stack_push (Stack_t* stack, elem_t value) 
{
    assert_ok  (stack);
    stack_null (stack);

    if ((stack -> size + 1) > (stack -> capacity)) 
    {
        stack_realloc (stack);
    }

    *(stack -> data + stack -> size) = value;
    stack -> size++;

    #ifdef PROTECTION
        stack -> hash = stack_hash (stack);
    #endif
    
    assert_ok (stack);
}

//-----------------------------------------------------------------------------------------

elem_t stack_pop (Stack_t* stack) 
{
    assert_ok  (stack);
    stack_null (stack);

    elem_t out = *(stack -> data + stack -> size - 1);

    poison_fill_in (stack, stack -> size - 1, stack -> size);

    stack -> size--;
    
    #ifdef PROTECTION
        stack -> hash = stack_hash (stack);
    #endif

    assert_ok (stack);

    return out;
}

//-----------------------------------------------------------------------------------------

void stack_destruct (Stack_t* stack) 
{
    assert_ok (stack);
    
    #ifdef PROTECTION
        free ((canary_t*) (stack -> data) - 1);
    #else
        free (stack -> data);
    #endif

    stack -> data                = nullptr;       
    stack -> size                = DATA_POISON; 
    stack -> error               = 0;           
    stack -> capacity            = DATA_POISON;             
    stack -> left_struct_canary  = Canary - 1;  
    stack -> right_struct_canary = Canary - 1;

    //assert_ok (stack);
}

//-----------------------------------------------------------------------------------------