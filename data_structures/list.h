#ifndef __defined_arraylist_h
#define __defined_arraylist_h

#include <stdlib.h>
#include <stdio.h>
#include "list.c"


typedef struct List List;

List* create_list();

void push_back(List* L, void* object);

void pop_front(List* L);

void pop_back(List* L);

void pop_current(List* L);

int is_empty(List* L);

int size(List* L);

void* first(List* L);

void* next(List* L);

void clear(List* L);



#endif /* __defined_arraylist_h */
