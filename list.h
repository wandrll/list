#pragma once
#include <stdio.h>

typedef double list_elem;

struct Node{
    list_elem value;
    int next;
    int prev;
};


struct List{
    Node* data;
    size_t size;
    size_t capacity;
    size_t free;
    size_t head;
    size_t tail;
    bool is_ordered;
};

enum list_codes{
    LIST_OK,
    LIST_CONSTRUCTOR_ERROR,
    LIST_DESTRUCTOR_ERROR,
    LIST_INCREASE_ERROR,
    LIST_DECREASE_ERROR,
    LIST_EMPTY,
    LIST_WRONG_INDEX
};

list_codes list_constructor(List* ls);
list_codes list_destructor(List* ls);

list_codes list_push_back(List* ls, list_elem value);
list_codes list_push_front(List* ls, list_elem value);

list_codes list_pop_back(List* ls, list_elem* value);
list_codes list_pop_front(List* ls, list_elem* value);

list_codes list_back(List* ls, list_elem* value);
list_codes list_front(List* ls, list_elem* value);

list_codes find_index_by_position(List* ls, size_t num, size_t* res);
list_codes list_insert(List* ls, list_elem value, size_t index);
list_codes list_erase(List* ls, list_elem* value, size_t index);

void list_dump_diag(List* ls);
void list_dump_file(List* ls);
