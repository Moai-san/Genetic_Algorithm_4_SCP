#include <stdio.h>
#include <stdlib.h>
//#include <dirent.h>
#include "./data_structures/list.h"
#include "./data_structures/treemap.h"
#include "./data_structures/city.c"
#include "./collect_data.c"

int myRand()
{
    return(rand()%MYRAND_MAX);
}

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

//prioridad de una solucion
float avgPriority()
{
    //TO-DO
    return(0);
}

int testing ()
{
    City** myCities = readCities();
    for (int i = 0; i < MYRAND_MAX; i++)
    {
        printf("%d\n",cityPriority(myCities[i][0].neighborhood));
    }
    
    return(0);   
}

int main()
{
    testing();
    /*for (int i = 0; i < 15; i++)
    {
        printf("%d\n",myRand());
    }*/
    return(0);
}