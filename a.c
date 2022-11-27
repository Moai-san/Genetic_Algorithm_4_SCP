#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "./lib/lectura_csv.c"
#include "./data_structures/list.h"
#include "./data_structures/treemap.h"

//si se cambia cantidad de columnas del dataset/ cantidad de ciudades, debe cambiarse el valor a ese
#define MYRAND_MAX 38

int myRand()
{
    return(rand()%MYRAND_MAX);
}

typedef struct City
{
    int id;
    char* name;
    List* neighborhood;
    int priority;
    float cost;
}City;

/* probably no use esto pq lo hice hace rato, y me vienen a la mente mas cosas
typedef struct Genoma
{
    int* values;
}Genoma;

typedef struct GenSet
{
    Genoma* parentList;
    Genoma* daughterList;
}GenSet;
//parentlist tiene los padres
//daughterlist los hijops
//actualizo padres y flusheo hijos

*/

/*
si quisiera que fuera determinista y sin heuristica
------------------------------------------------------------------
necesito que cada ciudad tenga dentro suyo puntero a sus vecinos (la verdad no, pero seria genial pq extenderia pa tsp probably)
necesito que tambien tenga el costo de poner una antena
por ultimo tambien su prioridad (cantidad de vecinos)
*/

//criterio de seleccion será elitista
//el genetico lo aplicaré en 1 corte y este será 
//el promedio de las prioridades (suma dividida en cantidad de ciudades)
//el costo total
//criterio elitista basado en costo, en el hipotetico caso de tener dos costos identicos, priorizaré la solucion de mayor promedio de prioridad
//criterio de salida será que el costo no disminuya al menos un 10%

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

//prioridad de una ciudad/nodo
int priority(List* nodoA)
{
    int output = 0;
    for (int i = 0; i < nodoA->count; i++)
    {
        int* temp =(int*)(nodoA->current->data);
        output = output+(*temp);
    }
    return output;
}

//prioridad de una solucion
float avgPriority()
{
    //TO-DO
    return(0);
}

int main()
{
    //testing();
    for (int i = 0; i < 15; i++)
    {
        printf("%d\n",myRand());
    }
    return(0);
}


int testing ()
{
    List* test1=create_list();
    List* test2=create_list();
    for (int i = 0; i < 5; i++)
    {
        int* value =(int*)calloc(1,sizeof(int));
        int* value2 =(int*)calloc(1,sizeof(int));
        *value=0;
        *value2=1;
        push_back(test1,value);
        push_back(test2,value2);
    }
    for (int i = 5; i < 10; i++)
    {
        int* value =(int*)calloc(1,sizeof(int));
        int* value2 =(int*)calloc(1,sizeof(int));
        *value=0;
        *value2=1;
        push_back(test1,value2);
        push_back(test2,value);
    }
    List* testSum=sumaNodos(test1,test2);
    //printf("%ld\n",testSum->count);
    printf("[");
    first(testSum);
    for (int i = 0; i < 10; i++)
    {
        printf("%d | ",*((int*)(testSum->current->data)));
        next(testSum);
    }
    return(0);   
}