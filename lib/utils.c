#include "../data_structures/list.h"

int myRand()
{
    return(rand()%(MYRAND_MAX));
}

int countAntennas(int* antennas)
{
    int output =0;
    for (int i = 0; i < MYRAND_MAX; i++)
    {
        if (antennas[i]==1)
        {
            output++;
        }
    }
    return output;
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

void sorteo(Solution** solutions)
{
    int i = 0;

    do
    {
        i++;

        if ((solutions[0]->costo) > (solutions[1]->costo))
        {
            Solution* aux = solutions[0];
            solutions[0] = solutions[1];
            solutions[1] = aux;
        }

        if ((solutions[2]->costo) > (solutions[3]->costo))
        {
            Solution* aux_2 = solutions[2];
            solutions[2] = solutions[3];
            solutions[3] = aux_2;
        }

        if ((i != 2) && ((solutions[1]->costo) > (solutions[2]->costo)))
        {
            Solution* aux_2 = solutions[1];
            solutions[1] = solutions[2];
            solutions[2] = aux_2;
        }
    } while (i != 2);

    return;
}

float getCosto(int* conf, City** myCities)
{
    float output =0;
    for (int i = 0; i < MYRAND_MAX; i++)
    {
        if (conf[i]==1)
        {
            output = output +myCities[i]->cost;
        }    
    }
    return output;
}

Solution* vec_toSol(int* vector,City** citySet)
{
    Solution* output = (Solution*)calloc(1,sizeof(Solution));
    output->solCities =create_list();
    output->costo =0;
    output->prioridad =0;
    output->coverage =citySet[0]->neighborhood;//vector vacio
    for (int i = 0; i < MYRAND_MAX; i++)
    {
        if (vector[i]==1)
        {
            push_back(output->solCities,citySet[i]);
            output->costo = output->costo+citySet[i]->cost;
            output->coverage =sumaNodos(output->coverage,citySet[i]->neighborhood);
            output->prioridad =output->prioridad+citySet[i]->priority;
        }
    }
    output->prioridad =output->prioridad/output->solCities->count;
    return(output);
}