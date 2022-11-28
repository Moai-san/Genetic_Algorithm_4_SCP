#include "./data_structures/solution.h"
#include "./lib/utils.c"
//tomo ciudades random hasta que generen una solucion factible
Solution** gen_initialSolutions(City** myCities)
{
    Solution** output =(Solution**)calloc(4,sizeof(Solution*));
    int banlist[38] ={0};
    banlist[0] =1;banlist[31]=1;
    int randNum;
    for (int i = 0; i < 4; i++)
    {
        Solution* solCandidate =(Solution*)calloc(1,sizeof(Solution));
        solCandidate->solCities =create_list();
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
            push_back(solCandidate->solCities,citPush);
            solCandidate->costo = (solCandidate->costo)+(citPush->cost);
            solCandidate->prioridad = (solCandidate->prioridad)+(citPush->priority);
            
            solCandidate->coverage = sumaNodos(solCandidate->coverage,citPush->neighborhood);
            if (isSolution((solCandidate->coverage))==1)
            {
                break;
            }
        }
        printVec(solCandidate->coverage);
        solCandidate->prioridad =(solCandidate->prioridad)/solCandidate->solCities->count;
        output[i]=solCandidate;
        for (int i = 0; i < MYRAND_MAX; i++)
        {
            banlist[i] =0;
        }
        banlist[0] =1;banlist[31] =1;
        
    }

    sorteo(output);
    return output;
}
