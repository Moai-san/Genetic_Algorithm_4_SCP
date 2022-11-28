#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./data_structures/list.h"
#include "./data_structures/treemap.h"
#include "./data_structures/city.c"
#include "./data_structures/solution.c"
#include "./genetico.c"
#include "./collect_data.c"

City** myCities;
Solution** solutions;

//criterio de seleccion será elitista
//el genetico lo aplicaré en 1 corte y este será 
//el promedio de las prioridades (suma dividida en cantidad de ciudades)
//el costo total
//criterio elitista basado en costo, en el hipotetico caso de tener dos costos identicos, priorizaré la solucion de mayor promedio de prioridad
//criterio de salida será que el costo no disminuya al menos un 10%

/*void podar()
{
    first(solutions);
    next(solutions);
    next(solutions);
    next(solutions);
}*/


//prioridad de una solucion
float avgPriority()
{
    //TO-DO
    return(0);
}

int testing ()
{
    //Solution* mysol =(Solution*)lastTreeMap(solutions);

    Solution* mysol0 =solutions[0];
    Solution* mysol1 =solutions[1];
    Solution* mysol2 =solutions[2];
    Solution* mysol3 =solutions[3];
    //printf("hola SEGFAULT\n");
    printf("%ld antenas en la solucion\n",mysol0->solCities->count);
    listAntenas(mysol0->solCities);
    //printf("$%.1fK USD, costo solucion\n\n",mysol->costo);
    printf("$%.1fK USD, costo solucion\n\n",mysol0->costo);
    printf("$%.1fK USD, costo solucion\n\n",mysol1->costo);
    printf("$%.1fK USD, costo solucion\n\n",mysol2->costo);
    printf("$%.1fK USD, costo solucion\n\n",mysol3->costo);
    return(0);   
}


int main()
{
    srand(time(NULL));
    myCities = readCities();
    solutions =(gen_initialSolutions(myCities));
    /*for (int i = 0; i < 4; i++)
    {
        printf("%.1f\n",solutions[i]->costo);
    }*/
    
    testing();
    return(0);
}