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


TEST(list_push_back, random_push_back_and_pop_back_test_with_resize){
    size_t count = 1000000;
    double* data = (double*)calloc(count, sizeof(double));
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    for(int i = 0; i < count; i++){
        tmp = ((int)rand()%400);
        data[i] = tmp;
        ASSERT_EQ(list_push_back(&lst, tmp), LIST_OK);
    }

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

TEST(list_push_back, _pub_puf_pob_pob){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    ASSERT_EQ(list_push_back(&lst, 10), LIST_OK);
    ASSERT_EQ(list_push_front(&lst, 1), LIST_OK);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);

    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

TEST(list_push_back, _pub_puf_pof_pob){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    ASSERT_EQ(list_push_back(&lst, 10), LIST_OK);
    ASSERT_EQ(list_push_front(&lst, 1), LIST_OK);

    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);

    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

TEST(list_push_back, _pub_puf_pob_pof){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    ASSERT_EQ(list_push_back(&lst, 10), LIST_OK);
    ASSERT_EQ(list_push_front(&lst, 1), LIST_OK);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);
    
    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);

    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

TEST(list_push_back, _pub_puf_pof_pof){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    ASSERT_EQ(list_push_back(&lst, 10), LIST_OK);
    ASSERT_EQ(list_push_front(&lst, 1), LIST_OK);

    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    
    ASSERT_EQ(list_pop_front(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);

    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

TEST(list_erase, mid){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 2, &index), LIST_OK);

    ASSERT_EQ(list_erase(&lst, &tmp, index), LIST_OK);
    ASSERT_EQ(tmp, 1);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, -1);
     
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

TEST(list_erase, first){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 1, &index), LIST_OK);

    ASSERT_EQ(list_erase(&lst, &tmp, index), LIST_OK);
    ASSERT_EQ(tmp, -1);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 10);
    
    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 1);
    
    ASSERT_EQ(lst.size, 0);

    list_destructor(&lst);
}

TEST(list_erase, last){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 4, &index), LIST_OK);

    ASSERT_EQ(list_erase(&lst, &tmp, index), LIST_OK);
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

TEST(list_erase, overflow){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    ASSERT_EQ(list_erase(&lst, &tmp, 100), LIST_WRONG_INDEX);
    ASSERT_EQ(tmp, 0);
    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}

TEST(list_erase, non_exist){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    ASSERT_EQ(list_erase(&lst, &tmp, 6), LIST_WRONG_INDEX);
    ASSERT_EQ(tmp, 0);
    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}


TEST(list_erase, fake_vertix){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    ASSERT_EQ(list_erase(&lst, &tmp, 0), LIST_WRONG_INDEX);
    ASSERT_EQ(tmp, 0);
    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}


TEST(list_insert, last){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 4, &index), LIST_OK);

    ASSERT_EQ(list_insert(&lst, 15, index), LIST_OK);
    ASSERT_EQ(lst.size, 5);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 15);

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


TEST(list_insert, mid1){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 1, &index), LIST_OK);

    ASSERT_EQ(list_insert(&lst, 15, index), LIST_OK);
    ASSERT_EQ(lst.size, 5);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);

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

TEST(list_insert, mid2){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 2, &index), LIST_OK);

    ASSERT_EQ(list_insert(&lst, 15, index), LIST_OK);
    ASSERT_EQ(lst.size, 5);

    ASSERT_EQ(list_pop_back(&lst, &tmp), LIST_OK);
    ASSERT_EQ(tmp, 12);

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

TEST(list_insert, overflow){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    ASSERT_EQ(list_insert(&lst, 10, 100),  LIST_WRONG_INDEX);
    ASSERT_EQ(tmp, 0);
    ASSERT_EQ(lst.size, 4);

    list_destructor(&lst);
}

TEST(list_insert, non_exist){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    ASSERT_EQ(list_insert(&lst, 10, 6),  LIST_WRONG_INDEX);
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

TEST(list_create_order, not_empty){
    List lst = {};
    list_constructor(&lst);

    double tmp = 0;

    FILL_LIST

    size_t index = 0;
    ASSERT_EQ(list_create_order(&lst), LIST_OK);
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



TEST(list_replace_value_by_index, ok){
    List lst = {};
    list_constructor(&lst);
    double tmp = 0;

    FILL_LIST
    
    size_t index = 0;   

    ASSERT_EQ(list_linear_find_index_by_position_if_isnt_ordered(&lst, 2, &index), LIST_OK);
    ASSERT_EQ(lst.size, 4);
    ASSERT_EQ(index, 2);

    ASSERT_EQ(list_replace_value_by_index(&lst, index, 228), LIST_OK);
    ASSERT_EQ(lst.size, 4);

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


int main(int argc, char *argv[])
{
    srand(time(NULL));

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}