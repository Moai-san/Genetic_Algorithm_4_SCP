//#include "list.h"
typedef struct Solution
{
    List* solCities;
    float costo;
    float prioridad;
    List* coverage;
}Solution;

int isSolution(List* coverage)
{
    if (coverage==NULL || coverage->count==0)
    {
        return 0;
    }
    
    first(coverage);

    for (int i = 0; i < MYRAND_MAX; i++)
    {
        if (i==0 || i==31)
        {
            next(coverage);
            continue;
        }
        
        int* cur =(int*)(coverage->current->data);
        if(*cur==0)
        {
            free(cur);
            return(0);
        }
        next(coverage);
    }
    return(1);
}