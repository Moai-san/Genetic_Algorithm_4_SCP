#include "./lib/lectura_csv.c"
//#include "./data_structures/city.c"

//prioridad de una ciudad/nodo
int cityPriority(List* nodoA)
{
    int output = 0;
    first(nodoA);
    for (int i = 0; i < nodoA->count; i++)
    {
        int* temp =(int*)(nodoA->current->data);
        output = output+(*temp);
        next(nodoA);
    }
    return output;
}

City** readCities()
{
    City** output =(City**)calloc(MYRAND_MAX,sizeof(City*));
    FILE* input;
    char line[2*MYRAND_MAX];
    input =fopen("./input_files/comunas.csv","r");
    int i =0;
    while(fgets(line,(2*MYRAND_MAX)+1,input) != NULL) //inicializacion de ciudades
    {
        int id =atoi(get_csv_field(line,0));
        char* name =(char*)get_csv_field(line,1);
        float cost =atof(get_csv_field(line,2));
        output[i] =(City*)calloc(1,sizeof(City));
        initializeCity(output[i],id,name,cost);
        i++;
    }
    fclose(input);
    i=0;
    input =fopen("./input_files/neighborhood_matrix.csv","r");
    while(fgets(line,(2*MYRAND_MAX)+1,input) != NULL) //adicion de vecindarios y prioridades
    {
        List* toPut=create_list();
        for (int j = 0; j < MYRAND_MAX; j++)
        {
            int* value =(int*)calloc(1,sizeof(int));
            *value =atoi(get_csv_field(line,j));
            push_back(toPut,value);
        }
        output[i][0].neighborhood =toPut;
        output[i][0].priority =cityPriority(toPut);
        i++;
    }
    fclose(input);
    return(output);
}