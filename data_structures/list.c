/**
 MIT License
 
 Copyright (c) 2018 Matias Barrientos.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "list.h"
#include <stdlib.h>
#include <assert.h>

typedef struct List List;
typedef struct Node Node;

static Node * createNode(void * data);

struct Node {
    /*! Puntero al dato */
    void * data;
    
    /*! Puntero al siguiente nodo */
    Node * next;
    
    /*! Puntero al anterior nodo */
    Node * prev;
};

struct List {
    /*! Puntero al incio (cabeza) de la lista */
    Node * head;
    
    /*! Puntero al final (cola) de la lista */
    Node * tail;
    
    /*! Punteor para poder recorrer la lista */
    Node * current;
    
    /*! Cantidad de elemento en la lista */
    long count;
};

static Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL); // No hay memoria para reservar el Nodo.
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * create_list() {
    List * new = (List *)malloc(sizeof(List));
    assert(new != NULL); // No hay memoria para reservar la Lista.
    new->head = new->tail = new->current = NULL;
    new->count = 0;
    return new;
}

long listCount(List * list) {
    assert(list != NULL); // list no puede ser NULL.
   
    if (list->head == NULL) return 0;
   
    return list->count;
}

int emptyList(List * list) {
    assert(list != NULL); // list no puede ser NULL.
    return list->count == 0;
}

void * first(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return NULL;
    
    list->current = list->head;
    
    return (void *)list->current->data;
}

void * next(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL || list->current == NULL || list->current->next == NULL) return NULL;
    
    list->current = list->current->next;
    
    return (void *)list->current->data;
}

void * last(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return NULL;
   
    list->current = list->tail;
    
    return (void *)list->current->data;
}

void * prev(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    
    list->current = list->current->prev;
    
    return (void *)list->current->data;
}

void push_front(List * list, void * data) {
    assert(list != NULL); // list no puede ser NULL.
    
    Node * new = createNode(data);
    
    if (list->head == NULL) {
        list->tail = new;
    } else {
        new->next = list->head;
        list->head->prev = new;
    }
    
    list->head = new;
    list->count += 1;
}

void push_back(List * list, void * data) {
    assert(list != NULL); // list no puede ser NULL.
    
    Node * new = createNode(data);
    
    if (list->head == NULL) {
        list->head = new;
    } else {
        list->tail->next = new;
        new->prev = list->tail;
    }
    
    list->tail = new;
    list->count += 1;
}

void push_current(List * list, void * data) {
    assert(list != NULL); // list no puede ser NULL.
    
    if (list->current == NULL) return;
    
    Node * new = createNode(data);
    
    new->next = list->current->next;
    new->prev = list->current;
    
    if (list->current->next != NULL) {
        list->current->next->prev = new;
    }
    
    list->current->next = new;
    
    if (list->current == list->tail) {
        list->tail = new;
    }
        
    list->count += 1;
}

void pop_front(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return;
    
    Node * aux = list->head;
    
    void * data = (void *)aux->data;
    
    if (list->head == list->tail) {
        list->tail = list->head = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    
    free(aux);
   
    list->count -= 1;

}

void pop_back(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return;
    
    Node * aux = list->tail;

    void * data = (void *)aux->data;

    if (list->tail == list->head) {
        list->tail = list->head = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    
    free(aux);
    
    list->count -= 1;
    
}

void pop_current(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL || list->current == NULL) return;
    
    Node * aux = list->current;
    
    if (list->current == list->head) {
        pop_front(list); return;
    } else if (list->current == list->tail) {
        pop_back(list); return;
    } else {
        if (aux->next != NULL) {
            aux->next->prev = aux->prev;
        }
        
        if (aux->prev != NULL) {
            aux->prev->next = aux->next;
        }
    }

    void * data = (void *)aux->data;
    
    list->current = aux->next;
    
    free(aux);
    
    list->count -= 1;

}

void removeAllList(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    while (list->head != NULL) {
        pop_front(list);
    }
}

