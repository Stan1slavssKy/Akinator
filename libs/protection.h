#ifndef PROTECTION_H_INCLUDED
#define PROTECTION_H_INCLUDED

#include "stack.h"

#define DATA_POISON -1

#ifdef DOUBLE_TYPE
    #define POISON_XXX NAN
#endif

#ifdef INT_TYPE
    #define POISON_XXX 0xBAADEDAA
#endif

#ifdef POINTER_TYPE
    #define POISON_XXX nullptr
#endif

//-----------------------------------------------------------------------------------------

#define NO_PROTECTION //подключение защиты 
// сделать флаг котоый говорит о защите!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#ifdef PROTECTION 
    #define assert_ok(stack) if (stack_ok(stack))    \
                             {                       \
                                 stack_dump (stack); \
                             }      
#else 
    #define assert_ok(stack) 1+1;                 
#endif 

//-----------------------------------------------------------------------------------------

#define error_case(enum_particle) case enum_particle:        \
                                      return #enum_particle; \

//-----------------------------------------------------------------------------------------

enum error
{
    MEMORY_OUT                = 1,
    NULL_DATA                 = 2,
    NEGATIVE_SIZE             = 3,
    NEGATIVE_CAPACITY         = 4,
    WRONG_CANARY_STRUCT_LEFT  = 5,
    WRONG_CANARY_STRUCT_RIGHT = 6,
    WRONG_CANARY_ARRAY_LEFT   = 7,
    WRONG_CANARY_ARRAY_RIGHT  = 8,
    WRONG_HASH                = 9
};

//-----------------------------------------------------------------------------------------

int    stack_ok       (Stack_t* stack);
size_t stack_hash     (Stack_t* stack);

void stack_dump       (Stack_t* stack);
void print_array      (Stack_t* stack);
void stack_null       (Stack_t* stack);
void poison_fill_in   (Stack_t* stack, size_t beg, size_t end);
void placing_canaries (Stack_t* stack, void* memory);

const char* error_detect  (Stack_t* stack);

//-----------------------------------------------------------------------------------------

#endif