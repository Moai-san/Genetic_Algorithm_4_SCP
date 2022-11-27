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
    //toInit.neighborhood =neighborhood;
    //toInit.priority =priority;
    (*toInit).cost =cost;
}