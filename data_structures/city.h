#include "list.h"

#define MYRAND_MAX 38

typedef struct City City;

void initializeCity(City* toInit, int id,char* name, float cost);
List* sumaNodos(List* nodoA, List* nodoB);
