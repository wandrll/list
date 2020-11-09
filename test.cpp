#include <gtest/gtest.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

#include "list.h"

#define FILL_LIST                                   \
    ASSERT_EQ(list_push_back(&lst, 10), LIST_OK);   \
    ASSERT_EQ(list_push_front(&lst, 1), LIST_OK);   \
                                                    \
    ASSERT_EQ(list_push_back(&lst, 12), LIST_OK);   \
    ASSERT_EQ(list_push_front(&lst, -1), LIST_OK);  

//0
TEST(list_push_pop, random_with_resize){
    size_t count = 300;
    double* data = (double*)calloc(count, sizeof(double));
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    for(int i = 0; i < count; i++){
        tmp = ((int)rand()%400);
        data[i] = tmp;
        ASSERT_EQ(list_push_back(&lst, tmp), LIST_OK);
    }
    list_dump_diag(&lst, "tests/0/5.pdf");
    for(int i = count-1; i >= 0; i--){
        ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
        ASSERT_EQ(tmp, data[i]);
    }

    for(int i = 0; i < count; i++){
        tmp = ((int)rand()%400);
        data[i] = tmp;
        ASSERT_EQ(list_push_back(&lst, tmp), LIST_OK);
    }

    for(int i = count-1; i >= 0; i--){
        ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
        ASSERT_EQ(tmp, data[i]);
    }
    
    free(data);

    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//1
TEST(list_push_pop, back_front_back_back){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    ASSERT_EQ(list_push_back(&lst, 10), LIST_OK);
    ASSERT_EQ(list_push_front(&lst, 1), LIST_OK);
    list_dump_diag(&lst, "tests/1/1.pdf");
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);
    list_dump_diag(&lst, "tests/1/2.pdf");
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    list_dump_diag(&lst, "tests/1/3.pdf");

    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//2
TEST(list_push_pop, back_front_front_back){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    ASSERT_EQ(list_push_back(&lst, 10), LIST_OK);
    ASSERT_EQ(list_push_front(&lst, 1), LIST_OK);
    list_dump_diag(&lst, "tests/2/1.pdf");

    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    list_dump_diag(&lst, "tests/2/2.pdf");
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);
    list_dump_diag(&lst, "tests/2/3.pdf");

    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//3
TEST(list_push_pop, back_front_back_front){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    ASSERT_EQ(list_push_back(&lst, 10), LIST_OK);
    ASSERT_EQ(list_push_front(&lst, 1), LIST_OK);
    list_dump_diag(&lst, "tests/3/1.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);
    list_dump_diag(&lst, "tests/3/2.pdf");

    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    list_dump_diag(&lst, "tests/3/3.pdf");

    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//4
TEST(list_push_pop, back_front_front_front){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    ASSERT_EQ(list_push_back(&lst, 10), LIST_OK);
    ASSERT_EQ(list_push_front(&lst, 1), LIST_OK);
    list_dump_diag(&lst, "tests/4/1.pdf");

    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    list_dump_diag(&lst, "tests/4/2.pdf");
    
    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);
    list_dump_diag(&lst, "tests/4/3.pdf");

    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//5
TEST(list_erase_by_index, mid){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 2, &index), LIST_OK);
    list_dump_diag(&lst, "tests/5/1.pdf");

    ASSERT_EQ(list_erase_by_index(&lst, &tmp, index), LIST_OK);
    ASSERT_EQ(tmp, 1);
    list_dump_diag(&lst, "tests/5/2.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);
    list_dump_diag(&lst, "tests/5/3.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
     
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//6
TEST(list_erase_by_index, first){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 1, &index), LIST_OK);
    list_dump_diag(&lst, "tests/6/1.pdf");

    ASSERT_EQ(list_erase_by_index(&lst, &tmp, index), LIST_OK);
    ASSERT_EQ(tmp, -1);
    list_dump_diag(&lst, "tests/6/2.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);
    list_dump_diag(&lst, "tests/6/3.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//7
TEST(list_erase_by_index, last){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 4, &index), LIST_OK);
    list_dump_diag(&lst, "tests/7/1.pdf");

    ASSERT_EQ(list_erase_by_index(&lst, &tmp, index), LIST_OK);
    ASSERT_EQ(tmp, 12);
    list_dump_diag(&lst, "tests/7/2.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
    
    ASSERT_EQ(lst.size, 0);


    list_destructor(&lst);
}

TEST(list_erase_by_index, overflow){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    ASSERT_EQ(list_erase_by_index(&lst, &tmp, 100), LIST_WRONG_INDEX);
    ASSERT_EQ(tmp, 0);
    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}

TEST(list_erase_by_index, non_exist){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    ASSERT_EQ(list_erase_by_index(&lst, &tmp, 6), LIST_WRONG_INDEX);
    ASSERT_EQ(tmp, 0);
    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}

TEST(list_erase_by_index, fake_vertix){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    ASSERT_EQ(list_erase_by_index(&lst, &tmp, 0), LIST_WRONG_INDEX);
    ASSERT_EQ(tmp, 0);
    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}

//8
TEST(list_insert_by_index, last){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 4, &index), LIST_OK);
    list_dump_diag(&lst, "tests/8/1.pdf");

    ASSERT_EQ(list_insert_by_index(&lst, 15, index), LIST_OK);
    ASSERT_EQ(lst.size, 5);
    list_dump_diag(&lst, "tests/8/2.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 15);
    list_dump_diag(&lst, "tests/8/3.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);
    
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
    
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}
 
//9
TEST(list_insert_by_index, mid1){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 1, &index), LIST_OK);
    list_dump_diag(&lst, "tests/9/1.pdf");

    ASSERT_EQ(list_insert_by_index(&lst, 15, index), LIST_OK);
    ASSERT_EQ(lst.size, 5);
    list_dump_diag(&lst, "tests/9/2.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);
    list_dump_diag(&lst, "tests/9/3.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 15);
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
    
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//10
TEST(list_insert_by_index, mid2){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 2, &index), LIST_OK);
    list_dump_diag(&lst, "tests/10/1.pdf");

    ASSERT_EQ(list_insert_by_index(&lst, 15, index), LIST_OK);
    ASSERT_EQ(lst.size, 5);
    list_dump_diag(&lst, "tests/10/2.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);
    list_dump_diag(&lst, "tests/10/3.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);
    
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 15);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
    
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

TEST(list_insert_by_index, overflow){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    ASSERT_EQ(list_insert_by_index(&lst, 10, 100),  LIST_WRONG_INDEX);
    ASSERT_EQ(tmp, 0);
    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}

TEST(list_insert_by_index, non_exist){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    ASSERT_EQ(list_insert_by_index(&lst, 10, 6),  LIST_WRONG_INDEX);
    ASSERT_EQ(tmp, 0);
    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}

TEST(list_create_order, empty){
    List lst = {};
    list_constructor(&lst);

    ASSERT_EQ(list_create_order(&lst), LIST_OK);    
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//11
TEST(list_create_order, not_empty){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST
    list_dump_diag(&lst, "tests/11/1.pdf");

    size_t index = 0;
    ASSERT_EQ(list_create_order(&lst), LIST_OK);
    list_dump_diag(&lst, "tests/11/2.pdf");

    ASSERT_EQ(lst.size, 4);

    ASSERT_EQ(list_get_value_by_index(&lst, 1, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);

    ASSERT_EQ(list_get_value_by_index(&lst, 2, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);

    ASSERT_EQ(list_get_value_by_index(&lst, 3, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);

    ASSERT_EQ(list_get_value_by_index(&lst, 4, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);

    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}

TEST(list_get_next_index, ok){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 1, &index), LIST_OK);
    ASSERT_EQ(lst.size, 4);
    ASSERT_EQ(index, 4);

    ASSERT_EQ(list_get_value_by_index(&lst, index, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);

    ASSERT_EQ(list_get_next_index(&lst, index, &index), LIST_OK);
    ASSERT_EQ(index, 2);

    ASSERT_EQ(list_get_value_by_index(&lst, index, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);

    
    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}

TEST(list_get_next_index, overflow){
    List lst = {};
    list_constructor(&lst);
    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;
   
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 4, &index), LIST_OK);
    ASSERT_EQ(lst.size, 4);
    ASSERT_EQ(index, 3);

    ASSERT_EQ(list_get_next_index(&lst, index, &index), LIST_OVERFLOW);
    ASSERT_EQ(index, 3);
    
    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}

TEST(list_get_prev_index, ok){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 3, &index), LIST_OK);
    ASSERT_EQ(lst.size, 4);
    ASSERT_EQ(index, 1);

    ASSERT_EQ(list_get_value_by_index(&lst, index, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);

    ASSERT_EQ(list_get_next_index(&lst, index, &index), LIST_OK);
    ASSERT_EQ(index, 3);

    ASSERT_EQ(list_get_value_by_index(&lst, index, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);

    
    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}

TEST(list_get_prev_index, underflow){
    List lst = {};
    list_constructor(&lst);
    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;
   

    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 1, &index), LIST_OK);
    ASSERT_EQ(lst.size, 4);
    ASSERT_EQ(index, 4);

    ASSERT_EQ(list_get_prev_index(&lst, index, &index), LIST_UNDERFLOW);
    ASSERT_EQ(index, 4);
    
    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}

//12
TEST(list_replace_value_by_index, ok){
    List lst = {};
    list_constructor(&lst);
    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;   
    list_dump_diag(&lst, "tests/12/1.pdf");

    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 2, &index), LIST_OK);
    ASSERT_EQ(lst.size, 4);
    ASSERT_EQ(index, 2);

    ASSERT_EQ(list_replace_value_by_index(&lst, index, 228), LIST_OK);
    ASSERT_EQ(lst.size, 4);
    list_dump_diag(&lst, "tests/12/2.pdf");

    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
    
    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 228);

    ASSERT_EQ(lst.size, 2);


    list_destructor(&lst);
}

TEST(list_replace_value_by_index, overflow){
    List lst = {};
    list_constructor(&lst);
    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;   

    ASSERT_EQ(list_replace_value_by_index(&lst, 100, 228), LIST_OVERFLOW);
    ASSERT_EQ(lst.size, 4);

    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
    
    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);

    ASSERT_EQ(lst.size, 2);


    list_destructor(&lst);
}

TEST(list_replace_value_by_index, wrong_index){
    List lst = {};
    list_constructor(&lst);
    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;   

    ASSERT_EQ(list_replace_value_by_index(&lst, 7, 228), LIST_WRONG_INDEX);
    ASSERT_EQ(lst.size, 4);

    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
    
    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);

    ASSERT_EQ(lst.size, 2);


    list_destructor(&lst);
}

TEST(list_validation, destroy_cycle){
    List lst = {};
    list_constructor(&lst);
    double tmp = 0;

    FILL_LIST
    lst.data[3].next = 4;
    
    ASSERT_EQ(list_erase_by_index(&lst, &tmp, 1), LIST_CORRUPTED);

    list_destructor(&lst);
}

//13
TEST(list_erase_by_position, mid){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;
    list_dump_diag(&lst, "tests/13/1.pdf");

    ASSERT_EQ(list_erase_by_position(&lst, &tmp, 2), LIST_OK);
    ASSERT_EQ(tmp, 1);
    list_dump_diag(&lst, "tests/13/2.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);
    list_dump_diag(&lst, "tests/13/3.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
     
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//14
TEST(list_erase_by_position, first){

    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;
    list_dump_diag(&lst, "tests/14/1.pdf");

    ASSERT_EQ(list_erase_by_position(&lst, &tmp, 1), LIST_OK);
    ASSERT_EQ(tmp, -1);
    list_dump_diag(&lst, "tests/14/2.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);
    list_dump_diag(&lst, "tests/14/3.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
     
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//15
TEST(list_erase_by_position, last){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;
    list_dump_diag(&lst, "tests/15/1.pdf");

    ASSERT_EQ(list_erase_by_position(&lst, &tmp, 4), LIST_OK);
    ASSERT_EQ(tmp, 12);
    list_dump_diag(&lst, "tests/15/2.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);
    list_dump_diag(&lst, "tests/15/3.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
     
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//16
TEST(list_insert_by_position, last){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    list_dump_diag(&lst, "tests/16/1.pdf");

    ASSERT_EQ(list_insert_by_position(&lst, 15, 4), LIST_OK);
    ASSERT_EQ(lst.size, 5);
    list_dump_diag(&lst, "tests/16/2.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 15);
    list_dump_diag(&lst, "tests/16/3.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);
    
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
    
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//17
TEST(list_insert_by_position, mid){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    list_dump_diag(&lst, "tests/17/1.pdf");

    ASSERT_EQ(list_insert_by_position(&lst, 15, 2), LIST_OK);
    ASSERT_EQ(lst.size, 5);
    list_dump_diag(&lst, "tests/17/2.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);
    list_dump_diag(&lst, "tests/17/3.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);
    
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 15);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
    
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//18
TEST(list_insert_by_position, first){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    list_dump_diag(&lst, "tests/18/1.pdf");

    ASSERT_EQ(list_insert_by_position(&lst, 15, 0), LIST_OK);
    ASSERT_EQ(lst.size, 5);
    list_dump_diag(&lst, "tests/18/2.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);
    list_dump_diag(&lst, "tests/18/3.pdf");

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);
    
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 15);
    
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

//19
TEST(list_replace_value_by_position, all){
    List lst = {};
    list_constructor(&lst);
    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;   
    list_dump_diag(&lst, "tests/19/1.pdf");

    ASSERT_EQ(list_replace_value_by_position(&lst, 1, 1), LIST_OK);
    ASSERT_EQ(list_replace_value_by_position(&lst, 2, 2), LIST_OK);
    ASSERT_EQ(list_replace_value_by_position(&lst, 3, 3), LIST_OK);
    ASSERT_EQ(list_replace_value_by_position(&lst, 4, 4), LIST_OK);
    list_dump_diag(&lst, "tests/19/2.pdf");

    ASSERT_EQ(lst.size, 4);

    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    
    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 2);

    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 3);
    
    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 4);

    ASSERT_EQ(lst.size, 0);


    list_destructor(&lst);
}


// -1 1 10 12//
int main(int argc, char *argv[])
{
    srand(time(NULL));

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}