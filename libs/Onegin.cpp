#include "Onegin.h"

char* read_file (char* file_name, int size_of_file)
{
    FILE* file = fopen (file_name, "rb");
    assert (file != nullptr);

    char* file_buffer = (char*) calloc (size_of_file, sizeof(char));
    assert (file_buffer);

    fread  (file_buffer, sizeof (char), size_of_file, file);
    fclose (file);

    return file_buffer;
}

//------------------------------------------------------------------------------------------------

int counter_line (char* file_buffer)
{
    assert (file_buffer != nullptr);

    char* beg_line     = file_buffer;
    char* end_line     = nullptr;
    int   line_counter = 0;

    while ((end_line = strchr (beg_line, '\n')) != nullptr)
    {
        beg_line = end_line + 1;
        line_counter++;
    }

    printf ("The number of rows is %d\n", line_counter);

    return line_counter;
}

//------------------------------------------------------------------------------------------------

int file_size (char* file_name)
{
    assert (file_name != nullptr);

    struct stat information_buffer = {};

    stat (file_name, &information_buffer);
    printf ("Size of \"%s\" is: %ld bytes.\n", file_name, information_buffer.st_size);

    return information_buffer.st_size;
}

//------------------------------------------------------------------------------------------------

void input_inform (char* file_name, struct text* text_info)
{
    assert (file_name != nullptr);
    assert (text_info != nullptr);

    int  size_of_file = file_size (file_name);
    char* file_buffer = read_file (file_name, size_of_file);

    text_info -> size_of_file = size_of_file;
    text_info -> file_buffer  = file_buffer;
}

//------------------------------------------------------------------------------------------------

void free_memory (struct text* text_info)
{
    assert (text_info                != nullptr);
    assert (text_info -> strings     != nullptr);
    assert (text_info -> file_buffer != nullptr);

    free (text_info -> strings);
    text_info -> strings = nullptr;

    free (text_info -> file_buffer);   
    text_info -> file_buffer = nullptr;
}

//------------------------------------------------------------------------------------------------

char* console_input (int argc, char* argv[])
{
    char* file_name = nullptr;

    if (argc == 2)
    {
        file_name = argv[1];
        printf ("You want read \"%s\"\n", file_name);
        return file_name;
    }
    
    if (argc == 1)
    {
        printf ("You didn't enter the file name. Please return program and enter file name.\n");
        return nullptr;
    }
    
    printf ("Error: to few or too many arguments.\n");
    return nullptr;
}

//------------------------------------------------------------------------------------------------