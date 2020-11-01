#include <stdio.h>
#include "list.h"

int main(){
    List lst = {};
    list_constructor(&lst);

    remove("log.txt");
    list_dump_file(&lst);

    list_push_front(&lst, 2);
    double tmp = 0;
    list_pop_front(&lst, &tmp);

    list_push_front(&lst, 1);
    list_dump_file(&lst);

    

    list_push_back(&lst, 11);
    list_push_back(&lst, 12);
    list_push_back(&lst, 13);
    list_dump_file(&lst);
list_pop_back(&lst, &tmp);
    list_dump_file(&lst);

    list_pop_front(&lst, &tmp);
    list_dump_file(&lst);

    list_pop_back(&lst, &tmp);
    list_dump_file(&lst);
    list_push_back(&lst, 14);
    list_push_front(&lst, 0);
    list_push_back(&lst, 16);
    list_push_back(&lst, 17);
   /* list_push_front(&lst, 9);
    list_push_front(&lst, 8);
    list_dump_file(&lst);

    //list_push_back(&lst, 12);
    double res = 0;
    list_push_front(&lst, 7);
  //  list_push_back(&lst, 13);
  //  list_push_back(&lst, 14);
    list_dump_file(&lst);

    //list_push_back(&lst, 15);
   // list_push_front(&lst, 5);
    size_t ind = 0;
   // find_index_by_position(&lst, 6, &ind);
   // printf("%ld ", ind);
    list_insert(&lst, 225, 8);
    list_dump_file(&lst);

   list_push_back(&lst, 15);*/
    list_dump_file(&lst);

    //list_insert(&lst, 225, ind);
    //list_dump_file(&lst);
    list_erase(&lst, &tmp, 7);
    list_dump_file(&lst);

    list_dump_diag(&lst);


  //  list_push_back(&lst, 11);
  //  list_push_front(&lst, 9);
  //  list_push_front(&lst, 8);
  //  list_dump_file(&lst);
//
  //  list_push_back(&lst, 12);
  //  list_push_back(&lst, 10);
  //  list_dump_file(&lst);
//
  //  list_push_back(&lst, 11);
  //  list_push_front(&lst, 9);
  //  list_push_front(&lst, 8);
  //  list_push_back(&lst, 12);
  //  list_push_back(&lst, 10);
  //  list_push_back(&lst, 11);
  //  list_push_front(&lst, 9);
  //  list_push_front(&lst, 8);
  //  list_push_back(&lst, 12);
  //  list_dump_file(&lst);
    //list_dump_diag(&lst);

    list_destructor(&lst);
    return 0;
}