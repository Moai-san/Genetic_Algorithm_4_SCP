#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./data_structures/list.h"
#include "./data_structures/treemap.h"
#include "./data_structures/city.c"
#include "./data_structures/solution.c"
#include "./genetico.c"
#include "./collect_data.c"

static City** myCities;
static TreeMap* solutions;

//criterio de seleccion será elitista
//el genetico lo aplicaré en 1 corte y este será 
//el promedio de las prioridades (suma dividida en cantidad de ciudades)
//el costo total
//criterio elitista basado en costo, en el hipotetico caso de tener dos costos identicos, priorizaré la solucion de mayor promedio de prioridad
//criterio de salida será que el costo no disminuya al menos un 10%

//prioridad de una solucion
float avgPriority()
{
    //TO-DO
    return(0);
}

int testing ()
{
    Solution* mysol =(Solution*)firstTreeMap(solutions);
    Solution* mysol2 =(Solution*)nextTreeMap(solutions);
    Solution* mysol3 =(Solution*)nextTreeMap(solutions);
    Solution* mysol4 =(Solution*)nextTreeMap(solutions);
    printf("%ld antenas en la solucion\n",mysol->solCities->count);
    listAntenas(mysol->solCities);
    printf("$%.1fK USD, costo solucion\n\n",mysol->costo);
    printf("$%.1fK USD, costo solucion\n\n",mysol2->costo);
    printf("$%.1fK USD, costo solucion\n\n",mysol3->costo);
    printf("$%.1fK USD, costo solucion\n\n",mysol4->costo);
    return(0);   
}


int main()
{
    srand(time(NULL));
    myCities = readCities();
    solutions =gen_initialSolutions(myCities);
    /*for (int i = 0; i < 4; i++)
    {
        printf("%f",*((float*)solutions->current->key));
    }*/
    
    testing();
    return(0);
}