#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./data_structures/list.h"
#include "./data_structures/treemap.h"
#include "./data_structures/city.c"
#include "./data_structures/solution.c"
#include "./genetico.c"
#include "./collect_data.c"

City** myCities; //Coleccion ciudades, sacadas del cruce de neighborhood_matrix.csv y comunas.csv
Solution** solutions; //Coleccion ciudades, sacadas del cruce de neighborhood_matrix.csv y comunas.csv

List* crossover(Solution* p1s, Solution* p2s,List* solutionsSet)
{
    //p1 y p2 arreglo de 0s y 1s solo con antenas
    int* p1 =genVectorAntenas(p1s->solCities);
    int* p2 =genVectorAntenas(p2s->solCities);
    //vectores hijos, solo 0s y 1s de las antenas
    int* s1v =(int*)calloc(MYRAND_MAX,sizeof(int));
    int* s2v =(int*)calloc(MYRAND_MAX,sizeof(int));
    int cut =0; //variable donde se alojara el corte

    //en base a esto, pickeo un nro random el que me dice donde cortar
    while (cut<=0||cut>(MYRAND_MAX-1))
    {
        cut=myRand();
    }

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

    //muto 1 hijo
    for (int i = 0; i < MYRAND_MAX; i++)
    {
        int mutateProbability=myRand();
        //16% mutacion aprox, se skipean 0 y 31 al no existir
        if(mutateProbability<=6 && i!=0 && i!=31)
        {
            s1v[i]= !s1v[i];
        }
    }
    
    //muto el otro hijo
    for (int i = 0; i < MYRAND_MAX; i++)
    {
        int mutateProbability=myRand();
        //16% mutacion aprox, se skipean 0 y 31 al no existir
        if(mutateProbability<=6 && i!=0 && i!=31)
        {
            s2v[i]= !s2v[i];
        }
    }

    //Genero solucion en base a vector de antenas
    Solution* s1 =vec_toSol(s1v,myCities);

    if(isSolution(s1->coverage))
    {
        push_back(solutionsSet,s1);//Si la solucion es factible (cubre todas las ciudades), la añado al conjunto de hijos
    }

    //Genero solucion en base a vector de antenas
    Solution* s2 =vec_toSol(s2v,myCities);
    if(isSolution(s2->coverage))
    {
        push_back(solutionsSet,s2);//Si la solucion es factible (cubre todas las ciudades), la añado al conjunto de hijos
    }
    return(solutionsSet);//retorno el conjunto de hijos validos (pueden ser ambos, solo uno, o ninguno)
}


void newGeneration(Solution** parents)
{
    List* daughters =create_list();//lista soluciones hijas
    
    //6 cruzamientos validos posibles entre 4 padres, se añaden los hijos viables nacidos de los 6 crossovers a la lista
    daughters =crossover(parents[0], parents[1], daughters);
    daughters =crossover(parents[1], parents[2], daughters);
    daughters =crossover(parents[2], parents[3], daughters);
    daughters =crossover(parents[0], parents[3], daughters);
    daughters =crossover(parents[0], parents[2], daughters);
    daughters =crossover(parents[1], parents[3], daughters);
    
    first(daughters);
    for (int i = 0; i < daughters->count; i++)//Se recorre la lista y se seleccionan las mejores soluciones entre padres e hijos
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
        sorteo(parents);//orden descendente
    }
}

int testing ()
{

    Solution* mysol0 =solutions[0];
    Solution* mysol1 =solutions[1];
    Solution* mysol2 =solutions[2];
    Solution* mysol3 =solutions[3];
    printf("%ld antenas en la solucion optima (solucion mas barata)\n",mysol0->solCities->count);
    printf("Solucion optima: ");
    listAntenas(mysol0->solCities);
    printf("$%.1fK USD, costo solucion optima\n\n",mysol0->costo);
    printf("$%.1fK USD, costo solucion\n\n",mysol1->costo);
    printf("$%.1fK USD, costo solucion\n\n",mysol2->costo);
    printf("$%.1fK USD, costo solucion\n\n",mysol3->costo);
    printf("---------------------------------------------------------------------------------------\n\n");
    return(0);   
}


int main()
{
    srand(time(NULL));//seteo de semilla de random con reloj
    int timeLapse =15;
    myCities = readCities();
    solutions =(gen_initialSolutions(myCities));   
    printf("SOLUCIONES INICIALES\n");
    testing();
    time_t end = time (NULL) + timeLapse;
    while (time(NULL)<end)
    {
        newGeneration(solutions);
    }
    printf("SOLUCIONES FINALES\n");
    testing();
    return(0);
}