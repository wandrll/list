#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////CONSTRUCTOR && DESTRUCTOR////////////////////////////////////////////////////

list_codes list_constructor(List* ls){
    assert(ls != NULL);

    const int first_count = 10;
    
    ls->data = (Node*)calloc(first_count, sizeof(Node));
    if(ls->data == NULL){
        return LIST_CONSTRUCTOR_ERROR;
    }else{
        ls->size = 0;
        ls->capacity = first_count - 1;    
        ls->free = 1;
        ls->is_ordered = true;

        for(int i = 1; i < first_count; i++){
            ls->data[i].prev = -1;
            ls->data[i].next = i+1;
        }
        
        return LIST_OK;
    }
}


list_codes list_destructor(List* ls){
    assert(ls != NULL);

    free(ls->data);
    ls->head = 0;
    ls->tail = 0;
    ls->size = 0;
    ls->capacity = 0;
    ls->free = 0;
    ls->is_ordered = false;
    
    return LIST_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////PUSH  BACK && FRONT//////////////////////////////////////////////////////////


list_codes list_push_back(List* ls, list_elem value){
    assert(ls != NULL);
    list_codes code = list_insert(ls, value, ls->tail);
    if(code != LIST_OK){
        return code;
    }
    return LIST_OK;
}

list_codes list_push_front(List* ls, list_elem value){
    assert(ls != NULL);   
    list_codes code = list_insert(ls, value, 0); 
    if(code != LIST_OK){
        return code;
    }
    return LIST_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////POP BACK && FRONT////////////////////////////////////////////////////////////



list_codes list_pop_back(List* ls, list_elem* value){
    assert(ls != NULL);
    list_codes code = list_erase(ls, value, ls->tail);
    if(code != LIST_OK){
        return code;
    }
    return LIST_OK;
}

list_codes list_pop_front(List* ls, list_elem* value){
    assert(ls != NULL);
    list_codes code = list_erase(ls, value, ls->head);
    if(code != LIST_OK){
        return code;
    }
    return LIST_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////BACK && FRONT////////////////////////////////////////////////////////////////

list_codes list_back(List* ls, list_elem* value){
    assert(ls != NULL);

    if(ls->size == 0){
        return LIST_EMPTY;
    } 
    *value = ls->data[ls->tail].value;
    return LIST_OK;
}

list_codes list_front(List* ls, list_elem* value){
    assert(ls != NULL);

    if(ls->size == 0){
        return LIST_EMPTY;
    } 
    *value = ls->data[ls->head].value;
    return LIST_OK;
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////

list_codes find_index_by_position(List* ls, size_t pos, size_t* res){
    assert(ls != NULL);

    if(pos >= ls->size){
        return LIST_WRONG_INDEX;
    }
    size_t curr = 0;
    if(pos < ls->size/2){
        curr = ls->head;
        for(int i = 0; i < pos; i++){
            curr = ls->data[curr].next;
        }
    }else{
        curr = ls->tail;
        for(int i = 0; i < ls->size - pos - 1; i++){
            curr = ls->data[curr].prev;
        }
    }

    *res = curr;
    return LIST_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////INSERT///////////////////////////////////////////////////////////////////////

static list_codes list_increase_capacity(List* ls){
    assert(ls != NULL);

    Node* new_data = (Node*)calloc(2*(ls->capacity + 1), sizeof(Node));
    
    if(new_data == NULL){
        return LIST_INCREASE_ERROR;
    }
    
    int curr = 1;
    for(int i = ls->head; i != 0; i = ls->data[i].next){
        new_data[curr].value = ls->data[i].value;
        new_data[curr].prev = (curr - 1);
        new_data[curr].next = (curr + 1)%(ls->size + 1);
        curr++;
    }

    ls->is_ordered = true;
    for(int i = curr; i < 2*(ls->capacity + 1); i++){
        new_data[i].prev = -1;
        new_data[i].next = i+1;
    }

    ls->capacity = 2*(ls->capacity + 1) - 1;
    free(ls->data);
    ls->data = new_data;
    ls->head = 1;
    ls->tail = ls->size;
    ls->free = ls->size + 1;
    ls->data[0].next = 1;
    ls->data[0].prev = ls->size;
    return LIST_OK;
}






list_codes list_insert(List* ls, list_elem value, size_t index){
    assert(ls != NULL);
    if(ls->data[index].prev == -1 || index > ls->capacity){
        return LIST_WRONG_INDEX;
    }

    if(ls->tail != index){
        ls->is_ordered = false;
    }

    size_t next_free = ls->data[ls->free].next;
    ls->data[ls->free].value = value;
    
    ls->data[ls->free].prev = index;
    ls->data[ls->free].next = ls->data[index].next;

    ls->data[ls->data[ls->free].next].prev = ls->free;
    ls->data[ls->data[ls->free].prev].next = ls->free;
    printf("%ld ", ls->free);
    ls->free = next_free;
    ls->size++;

    if(ls->size == ls->capacity){
        if(list_increase_capacity(ls) == LIST_INCREASE_ERROR){
            return LIST_INCREASE_ERROR;
        }
    }
    
    ls->head = ls->data[0].next;
    ls->tail = ls->data[0].prev;

    return LIST_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////ERASE////////////////////////////////////////////////////////////////////////

static list_codes list_decrease_capacity(List* ls){
    assert(ls != NULL);

    Node* new_data = (Node*)calloc((ls->capacity + 1)/2, sizeof(Node));
    
    if(new_data == NULL){
        return LIST_INCREASE_ERROR;
    }
    
    size_t curr = 1;
    for(int i = ls->head; i != 0; i = ls->data[i].next){
        new_data[curr].value = ls->data[i].value;
        new_data[curr].prev = (curr - 1);
        new_data[curr].next = (curr + 1)%(ls->size + 1);
        curr++;
    }

    ls->is_ordered = true;
    for(int i = curr; i < (ls->capacity + 1)/2; i++){
        new_data[i].prev = -1;
        new_data[i].next = i+1;
    }
    
    ls->capacity = (ls->capacity + 1)/2 - 1;
    free(ls->data);
    ls->data = new_data;
    ls->head = 1;
    ls->tail = ls->size;
    ls->free = ls->size + 1;
    return LIST_OK;
}


list_codes list_erase(List* ls, list_elem* value, size_t index){
    assert(ls != NULL);
    
    if(ls->data[index].prev == -1 || index == 0 || index > ls->capacity){
        return LIST_WRONG_INDEX;
    }

    if(ls->tail != index){
        ls->is_ordered = false;
    }

    if(ls->tail != index){
        ls->is_ordered = false;
    }

    ls->data[ls->data[index].next].prev = ls->data[index].prev;
    ls->data[ls->data[index].prev].next = ls->data[index].next;

    *value = ls->data[index].value;
    ls->data[index].next = ls->free;
    ls->data[index].prev = -1;
    ls->data[index].value = 0;
    ls->free = index;
    

    ls->head = ls->data[0].next;
    ls->tail = ls->data[0].prev;

    return LIST_OK;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// DUMP //////////////////////////////////////////////////////////////////////

void list_dump_diag(List* ls){
    FILE* fp = fopen("res.gv", "w");
    fprintf(fp,"digraph G{\n");


    for(int curr = 1; curr <= ls->capacity; curr++){
        if(ls->data[curr].prev != -1){
            fprintf(fp, "\"%lg \\n ind = %d\"->\"%lg \\n ind = %d\"\n[color=\"red\"]", 
                                                                                ls->data[curr].value,
                                                                                curr,
                                                                                ls->data[ls->data[curr].next].value,
                                                                                ls->data[curr].next);
           // printf("(%lg, prev = %d next = %d)\n", ls->data[curr].value, ls->data[curr].prev, ls->data[curr].next);
            fprintf(fp, "\"%lg \\n ind = %d\"->\"%lg \\n ind = %d\"", ls->data[curr].value,
                                                                                curr,
                                                                                ls->data[ls->data[curr].prev].value,
                                                                                ls->data[curr].prev
                                                                                );                                                                    
        }
    }


    fprintf(fp,"}\n");
    fclose(fp);
    system("dot -Tpng res.gv -ores1.png");
}


void list_dump_file(List* ls){
    FILE* fp = fopen("log.txt", "a");
    fprintf(fp,"capacity: %ld\n size: %ld\n head: %ld\n tail: %ld\n free: %ld\n is ordered: %d\n", ls->capacity,
                                                                                               ls->size,
                                                                                               ls->head, 
                                                                                               ls->tail, 
                                                                                               ls->free, 
                                                                                               ls->is_ordered);


    for(int curr = 0; curr <= ls->capacity; curr++){
        fprintf(fp, "%5lg ", ls->data[curr].value);
    }
    fprintf(fp, "\n");

    for(int curr = 0; curr <= ls->capacity; curr++){
        fprintf(fp, "%5d ", ls->data[curr].next);
    }
    fprintf(fp, "\n");


    for(int curr = 0; curr <= ls->capacity; curr++){
        fprintf(fp, "%5d ", ls->data[curr].prev);
    }
    fprintf(fp,"\n-------------------------------------------\n");
    fclose(fp);
}
