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

int* genVectorAntenas(List* solCities)
{
    int* output =(int*)calloc(RAND_MAX,sizeof(int));
    City* awa;
    for (int j = 0; j < solCities->count; j++)
    {
        awa =(City*)solCities->current->data;
        output[awa->id]=1;
        next(solCities);
    }
    return(output);
}