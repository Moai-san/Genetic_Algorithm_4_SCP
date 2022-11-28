#include "../data_structures/list.h"

int myRand()
{
    return(rand()%(MYRAND_MAX));
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