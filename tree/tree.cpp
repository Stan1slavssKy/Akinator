#include "../akinator/akinator.h"

//===================================================================================

void tree_construct (tree_node* tree)
{

}

//===================================================================================
// Вход:      указатель на текущую структуру, структура дерева, структура акинатора
// О функции: проверка на то ноль ли текущий указатель, если нет, 
// то добавляем левого ребенка, если да - то присваеваем указатею  
// на текущий объект указатель на ребенка
// Выход:     указатель на левого ребенка

tree_node* add_left_child (tree_node* current_node, tree_node* tree, akinator_tree* aktr)
{
    tree_node* child_ptr = (tree_node*) calloc (1, sizeof (tree_node));
    assert (child_ptr);

    if (current_node == nullptr)
        aktr -> root = child_ptr;
    else 
        current_node -> left = child_ptr;
    
    return child_ptr;
}

//===================================================================================
// Вход:      указатель на текущую структуру, структура дерева, структура акинатора
// О функции: проверка на то ноль ли текущий указатель, если нет, 
// то добавляем левого ребенка, если да - то присваеваем указатею  
// на текущий объект указатель на ребенка
// Выход:     указатель на левого ребенка

tree_node* add_right_child (tree_node* current_node, tree_node* tree, akinator_tree* aktr)
{
    tree_node* child_ptr = (tree_node*) calloc (1, sizeof (tree_node));
    assert (child_ptr);

    if (current_node == nullptr)
        aktr -> root = child_ptr;
    else 
        current_node -> right = child_ptr;

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

void tree_fill_from_file ()
{

}

//===================================================================================

// Вход:      указатель на структуру, начиная с которой нужно удалить узлы
// О функции: освобождает узлы
// Выход:     нет

void node_destruct (tree_node* current_node)
{
    if (current_node == nullptr)
        return;

    node_destruct (current_node -> left);
    node_destruct (current_node -> right);

    free (current_node);
}

//===================================================================================
// Вход:      указатель на структуру, начиная с которой нужно удалить узлы
// О функции: освобождает узлы
// Выход:     нет

void tree_destuct (tree_node* current_node)
{
    if (current_node == nullptr)
    {
        return;
    }

    node_destruct (current_node -> left);
    node_destruct (current_node -> right);

    current_node -> left  = nullptr;
    current_node -> right = nullptr;

    free (current_node);
    current_node = nullptr;
}

//===================================================================================