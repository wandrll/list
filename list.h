#pragma once
#include <stdio.h>
#define DEBUG_ON

#ifdef DEBUG_ON
    #define IF_DEBUG_ON(code) code
#else
    #define IF_DEBUG_ON(code)
#endif


typedef double list_elem;

struct Node{
    list_elem value;
    int next;
    int prev;
};

struct Log_data{
    const char* file;
    const char* func;
    int line;
};

Log_data* create_log_data(const char* file, const char* func, int line);


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
    LIST_WRONG_INDEX,
    LIST_ORDER_ERROR,
    LIST_OVERFLOW,
    LIST_UNDERFLOW,
    LIST_CORRUPTED
};

list_codes list_constructor(List* ls);
list_codes list_destructor(List* ls);

list_codes list_push_back(List* ls, list_elem value);
list_codes list_push_front(List* ls, list_elem value);

list_codes list_pop_back(List* ls, list_elem* value);
list_codes list_pop_front(List* ls, list_elem* value);

list_codes list_back(List* ls, list_elem* value);
list_codes list_front(List* ls, list_elem* value);

list_codes list_linear_find_index_by_position_if_isnt_ordered(List* ls, size_t num, size_t* res);
list_codes list_get_next_index(List* ls, size_t ind, size_t* res);
list_codes list_get_prev_index(List* ls, size_t ind, size_t* res);
list_codes list_get_value_by_index(List* ls, size_t ind, list_elem* res);
list_codes list_get_value_by_position(List* ls, size_t pos, list_elem* res);
list_codes list_replace_value_by_index(List* ls, size_t ind, list_elem val);
list_codes list_replace_value_by_position(List* ls, size_t pos, list_elem val);


list_codes list_insert_by_index(List* ls, list_elem value, size_t index);
list_codes list_erase_by_index(List* ls, list_elem* value, size_t index);


list_codes list_insert_by_position(List* ls, list_elem value, size_t position);
list_codes list_erase_by_position(List* ls, list_elem* value, size_t position);


list_codes list_create_order(List* ls);

void list_dump_diag(List* ls, const char* file);
void list_dump_file(List* ls, const char* file);

bool list_validation(List* ls, Log_data* log);
