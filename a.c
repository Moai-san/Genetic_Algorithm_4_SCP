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

//luego de esto hago un for desde nRandom en adelante y s1v[i]=p2[i] y s2v[i]=p1[i]
List* crossover(Solution* p1s, Solution* p2s,List* solutionsSet)
{
    //printf("it2 \n\n");
    //p1 y p2 arreglo de 0s y 1s solo con antenas
    int* p1 =genVectorAntenas(p1s->solCities);
    int* p2 =genVectorAntenas(p2s->solCities);
    int* s1v =(int*)calloc(MYRAND_MAX,sizeof(int));
    int* s2v =(int*)calloc(MYRAND_MAX,sizeof(int));
    int cut =0;
    //en base a esto, pickeo un nro random el que me dice donde cortar
    while (cut<=0||cut>(MYRAND_MAX-1))
    {
        cut=myRand();
    }
    //printf("it2 \n\n");
    //cruzo los genes
    for (int i = 0; i < MYRAND_MAX; i++)
    {
        if (i>=cut)
        {
            s1v[i]=p2[i];
            s2v[i]=p1[i];
            continue;
        }
        s1v[i]=p1[i];//unreachable if i>=cut because continue skips all the following lines and iterate again
        s2v[i]=p2[i];//unreachable if i>=cut because continue skips all the following lines and iterate again
    }

    for (int i = 0; i < MYRAND_MAX; i++)
    {
        int mutateProbability=myRand();
        //16% mutacion aprox, se skipean 0 y 31 al no existir
        if(mutateProbability<=6 && i!=0 && i!=31)
        {
            s1v[i]= !s1v[i];
        }
    }
    
    for (int i = 0; i < MYRAND_MAX; i++)
    {
        int mutateProbability=myRand();
        //16% mutacion aprox, se skipean 0 y 31 al no existir
        if(mutateProbability<=6 && i!=0 && i!=31)
        {
            s2v[i]= !s2v[i];
        }
    }
    //printf("it2 \n\n");
    /*
    float costo =getCosto(s1v,myCities);
    for (int i = 0; i < 4; i++)
    {
        if(solutionsSet[i]->costo>costo)
        {
            free(solutionsSet[3]);
            solutionsSet[3]= vec_toSol(s1v,myCities);
            break;
        }
    }
    sorteo(solutionsSet);
    costo =getCosto(s2v,myCities);
    for (int i = 0; i < 4; i++)
    {
        if(solutionsSet[i]->costo>costo)
        {
            free(solutionsSet[3]);
            solutionsSet[3]= vec_toSol(s2v,myCities);
            break;
        }
    }*/
    Solution* s1 =vec_toSol(s1v,myCities);
    if(isSolution(s1->coverage))
    {
        push_back(solutionsSet,s1);
    }
    Solution* s2 =vec_toSol(s2v,myCities);
    if(isSolution(s2->coverage))
    {
        push_back(solutionsSet,s2);
    }
    return(solutionsSet);
    //despues comparo valores con cada uno de los padres y lo agrego al arreglo de soluciones en caso de ser mejor
}

void newGeneration(Solution** parents)
{
    List* daughters =create_list();
    daughters =crossover(parents[0], parents[1], daughters);
    daughters =crossover(parents[1], parents[2], daughters);
    daughters =crossover(parents[2], parents[3], daughters);
    daughters =crossover(parents[0], parents[3], daughters);
    daughters =crossover(parents[0], parents[2], daughters);
    daughters =crossover(parents[1], parents[3], daughters);
    
    first(daughters);
    for (int i = 0; i < daughters->count; i++)
    {
        for (int i = 0; i < 4; i++)
        {
            Solution* sol =(Solution*)daughters->current->data;
            if(parents[i]->costo>sol->costo)
            {
                free(parents[3]);
                parents[3]= sol;
                break;
            }
        }
        next(daughters);
        sorteo(parents);
    }
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
    int timeLapse =15;
    myCities = readCities();
    solutions =(gen_initialSolutions(myCities));   
    testing();
    time_t end = time (NULL) + timeLapse;
    while (time(NULL)<end)
    {
        newGeneration(solutions);
        testing();
    }

    //testing();
    return(0);
}