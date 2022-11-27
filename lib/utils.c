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