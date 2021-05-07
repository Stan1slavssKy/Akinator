#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

#include <stdio.h>                
#include <stdlib.h>               
#include <string.h>               
#include <sys/stat.h>             
#include <sys/types.h>            
#include <locale.h>               
#include <ctype.h>
#include <assert.h>

//------------------------------------------------------------------------------------------------

struct text 
{
    int  size_of_file   = 0;
    char* file_buffer   = nullptr;
    struct str* strings = nullptr;
};
//сделать флаг который будет выбирать структуру по надобности

struct str
{
    char* p_begin_str;
    int   str_length;
};

//------------------------------------------------------------------------------------------------

char* console_input (int argc, char* argv[]);

char* read_file    (char* file_name, int size_of_file);
int   file_size    (char* file_name);
int  counter_line  (char* file_buffer);
void input_inform  (char* file_name, struct text* text_info);

void lexemes_parsing  (struct text* text_info);
void place_pointers   (struct text* text_info);
void free_memory      (struct text* text_info);

//------------------------------------------------------------------------------------------------

#endif 