#include "tree.h"
#include "../akinator/akinator.h"

//===================================================================================

void tree_construct (tree_node* tree)
{
           
}

//===================================================================================
// Вход:      указатель на текущую структуру, структура дерева, структура акинатора
// О функции: проверка на то ноль ли текущщий указатель, если нет, 
// то добавляем левого ребенка, если да - то присваеваем указатею  
// на текущий объект указатель на ребенка
// Выход:     указатель на левого ребенка

tree_node* add_left_child (tree_node* object, tree_node* tree, akinator* aktr)
{
    tree_node* child_ptr = (tree_node*) calloc (1, sizeof (tree_node));
    assert (child_ptr);

    if (object == nullptr)
        aktr -> root = child_ptr;
    else 
        object -> left = child_ptr;
    
    return child_ptr;
}

//===================================================================================
// Вход:      указатель на текущую структуру, структура дерева, структура акинатора
// О функции: проверка на то ноль ли текущщий указатель, если нет, 
// то добавляем левого ребенка, если да - то присваеваем указатею  
// на текущий объект указатель на ребенка
// Выход:     указатель на левого ребенка

tree_node* add_left_child (tree_node* object, tree_node* tree, akinator* aktr)
{
    tree_node* child_ptr = (tree_node*) calloc (1, sizeof (tree_node));
    assert (child_ptr);

    if (object == nullptr)
        aktr -> root = child_ptr;
    else 
        object -> right = child_ptr;

    return child_ptr;
}

//===================================================================================

void tree_dump ()
{

}

//===================================================================================

void print_node ()
{

}

//===================================================================================
// Вход:      указатель на структуру, начиная с которой нужно удалить узлы
// О функции: освобождает узлы
// Выход:     нет

void node_destruct (tree_node* object)
{
    if (object == nullptr)
        return;

    node_destruct (object -> left);
    node_destruct (object -> right);

    free (object);
}

//===================================================================================
// Вход:      указатель на структуру, начиная с которой нужно удалить узлы
// О функции: освобождает узлы
// Выход:     нет

void tree_destuct (tree_node* object)
{
    if (object == nullptr)
        return;
    
    node_destruct (object -> left);
    node_destruct (object -> right);

    object -> left  = nullptr;
    object -> right = nullptr;
}

//===================================================================================