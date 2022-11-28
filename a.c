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

/*
1-2
2-3
3-4
1-4
1-3
2-4
*/

Solution** genSons(Solution** parents)
{
    parents[0], parents[1];
    parents[1], parents[2];
    parents[2], parents[3];
    parents[0], parents[3];
    parents[0], parents[2];
    parents[1], parents[3];
}

//luego de esto hago un for desde nRandom en adelante y s1[i]=p2[i] y s2[i]=p1[i]
Solution* crossover(Solution* p1s, Solution* p2s)
{
    //p1 y p2 arreglo de 0s y 1s solo con antenas
    int* p1 =genVectorAntenas(p1s->solCities);
    int* p2 =genVectorAntenas(p2s->solCities);
    int* s1 =(int*)calloc(MYRAND_MAX,sizeof(int));
    int* s2 =(int*)calloc(MYRAND_MAX,sizeof(int));
    int cut =0;

    //en base a esto, pickeo un nro random el que me dice donde cortar
    while (cut==0||cut>(RAND_MAX-1))
    {
        cut=myRand();
    }
    //cruzo los genes
    for (int i = 0; i < RAND_MAX; i++)
    {
        if (i>=cut)
        {
            s1[i]=p2[i];
            s2[i]=p1[i];
            continue;
        }
        s1[i]=p1[i];//unreachable if i>=cut because continue skips all the following lines and iterate again
        s2[i]=p2[i];//unreachable if i>=cut because continue skips all the following lines and iterate again
    }

    for (int i = 0; i < RAND_MAX; i++)
    {
        int mutateProbability=myRand();
        //16% mutacion aprox, se skipean 0 y 31 al no existir
        if(mutateProbability<=6 && i!=0 && i!=31)
        {
            s1[i]= !s1[i];
        }
    }
    
    for (int i = 0; i < RAND_MAX; i++)
    {
        int mutateProbability=myRand();
        //16% mutacion aprox, se skipean 0 y 31 al no existir
        if(mutateProbability<=6 && i!=0 && i!=31)
        {
            s2[i]= !s2[i];
        }
    }
    //despues comparo valores con cada uno de los padres y lo agrego al arreglo de soluciones en caso de ser mejor

}

//prioridad de una solucion
float avgPriority()
{
    //TO-DO
    return(0);
}

int testing ()
{

    Solution* mysol0 =solutions[0];
    Solution* mysol1 =solutions[1];
    Solution* mysol2 =solutions[2];
    Solution* mysol3 =solutions[3];
    printf("%ld antenas en la solucion\n",mysol0->solCities->count);
    listAntenas(mysol0->solCities);
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
    testing();
    return(0);
}