#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./data_structures/list.h"
#include "./data_structures/treemap.h"
#include "./data_structures/city.c"
#include "./data_structures/solution.c"
#include "./collect_data.c"

static City** myCities;
static TreeMap* solutions;

int myRand()
{
    return(rand()%(MYRAND_MAX));
}

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


void printVec(List* vec)
{
    printf("[ ");
    first(vec);
    for (int i = 0; i < vec->count; i++)
    {
        if (i==vec->count-1)
        {
            printf("%d ]\n",*(int*)(vec->current->data));
            return;
        }
        printf("%d |",*(int*)(vec->current->data));
        next(vec);
    }
    
}

int isBanned(int banlist[],int number)
{
    if (banlist[number]==1)
    {
        return 1;
    }
    return 0;
}

void listAntenas(List* solCities)
{
    printf("Antenas situadas en: ");
    first(solCities);
    for (int j = 0; j < solCities->count; j++)
    {
        City* awa =(City*)solCities->current->data;
        printf("%d",awa->id);
        if (j<(solCities->count)-1)
        {
            printf(", ");
        }
        next(solCities);
    }
    printf("\n");
}

//tomo ciudades random hasta que generen una solucion factible
TreeMap* genSolutions()
{
    TreeMap* output =createTreeMap(lower_than_int);
    int banlist[38] ={0};
    banlist[0] =1;banlist[31]=1;
    int randNum;
    for (int i = 0; i < 4; i++)
    {
        List* list_toPush =create_list();
        Solution* solCandidate =(Solution*)calloc(1,sizeof(Solution));
        solCandidate->coverage =create_list();
        *(solCandidate->coverage) =*(myCities[0][0].neighborhood); //la ciudad 0 no existe asi que es un vector vacío
        solCandidate->costo =0;
        solCandidate->prioridad =0;
        while(1)
        {
            randNum =myRand();
            if ((isBanned(banlist,randNum)==1)||(randNum>37))
            {
                continue;
            }
            City* citPush =(City*)calloc(1,sizeof(City));
            *citPush =myCities[randNum][0];
            banlist[randNum] =1;
            push_back(list_toPush,citPush);
            solCandidate->costo = (solCandidate->costo)+(citPush->cost);
            solCandidate->prioridad = (solCandidate->prioridad)+(citPush->priority);
            
            solCandidate->coverage = sumaNodos(solCandidate->coverage,citPush->neighborhood);
            if (isSolution((solCandidate->coverage))==1)
            {
                break;
            }
        }
        solCandidate->solCities=list_toPush;
        printVec(solCandidate->coverage);
        solCandidate->prioridad =(solCandidate->prioridad)/list_toPush->count;
        insertTreeMap(output,&(solCandidate->costo),solCandidate);
        for (int i = 0; i < MYRAND_MAX; i++)
        {
            banlist[i] =0;
        }
        banlist[0] =1;banlist[31] =1;
        
    }
    return output;
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
    solutions =genSolutions();
    /*for (int i = 0; i < 4; i++)
    {
        printf("%f",*((float*)solutions->current->key));
    }*/
    
    testing();
    return(0);
}