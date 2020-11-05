#include <stdio.h>
#include "list.h"

int main(){
    List lst = {};
    list_constructor(&lst);

    remove("log.txt");
    //list_dump_file(&lst);
    list_dump_file(&lst, "log.txt");

    list_push_front(&lst, 2);
    list_dump_file(&lst, "log.txt");

    double tmp = 0;
    //list_dump_file(&lst);

    list_pop_front(&lst, &tmp);
    list_dump_file(&lst, "log.txt");

    list_push_front(&lst, 2);
    list_dump_file(&lst, "log.txt");
    //list_dump_file(&lst);

    
    list_push_front(&lst, 1);
    list_dump_file(&lst, "log.txt");
    list_push_back(&lst, 11);
    list_dump_file(&lst, "log.txt");
    list_push_back(&lst, 12);
    list_dump_file(&lst, "log.txt");
    list_push_back(&lst, 13);
    list_dump_file(&lst, "log.txt");
    //list_dump_file(&lst);
    list_pop_back(&lst, &tmp);
    list_dump_file(&lst, "log.txt");
    //list_dump_file(&lst);

    list_pop_front(&lst, &tmp);
    list_dump_file(&lst, "log.txt");
    //list_dump_file(&lst);

    list_pop_back(&lst, &tmp);
    list_dump_file(&lst, "log.txt");
    list_push_back(&lst, 14);
    list_dump_file(&lst, "log.txt");
    //list_dump_file(&lst);

    list_push_front(&lst, 15);
    list_push_front(&lst, -1);
     list_dump_file(&lst, "log.txt");
    list_push_back(&lst, 11);
    list_dump_file(&lst, "log.txt");
    list_push_back(&lst, 12);
    list_dump_file(&lst, "log.txt");
    list_push_back(&lst, 13);
    list_dump_file(&lst, "log.txt");
     list_dump_file(&lst, "log.txt");
    list_push_back(&lst, 11);
    list_dump_file(&lst, "log.txt");
    list_push_back(&lst, 12);
    list_dump_file(&lst, "log.txt");
    list_push_back(&lst, 13);
    list_dump_file(&lst, "log.txt");
            list_dump_diag(&lst, "1/error.png");

    list_push_front(&lst, -2);
    list_push_front(&lst, -4);
    list_push_front(&lst, -10);

    list_dump_file(&lst, "log.txt");

    list_create_order(&lst);
    list_dump_file(&lst, "log.txt");

    list_dump_file(&lst, "log.txt");


    list_destructor(&lst);
    return 0;
}