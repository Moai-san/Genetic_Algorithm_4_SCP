#include "list.h"

//si se cambia cantidad de columnas del dataset/ cantidad de ciudades, debe cambiarse el valor a ese menos 1
#define MYRAND_MAX 38

typedef struct City
{
    int id;
    char* name;
    List* neighborhood;
    int priority;
    float cost;
}City;

//Constructor
void initializeCity(City* toInit, int id,char* name, float cost)
{
    (*toInit).id =id;
    (*toInit).name =name;
    (*toInit).cost =cost;
}

//para generar soluciones inciales, se pasan 2 nodos/ciudades por un OR, y asi se genera un vector de ciudades cubiertas
List* sumaNodos(List* nodoA, List* nodoB)
{
    List* output=create_list();
    first(nodoA);
    first(nodoB);
    for(int i =0; i<nodoA->count; i++)
    {
        int* valA =(int*)(nodoA->current->data);
        int* valB =(int*)(nodoB->current->data);
        int* toPush = (int*)calloc(1,sizeof(int));
        *toPush= (*valA||*valB);
        push_back(output,toPush);
        next(nodoA);
        next(nodoB);
    }
    return output;
}