#include "solution_method.h"
#include <string.h>


double Solution_method::get(std::string var, const int k /*= -1*/)
{
//    char name [255];
//    if (k >=0)
//        sprintf(name, "%s%d", var,k);
//    else
//        strcpy(name, var);

    std::string name;
    name = var;
    if (Solution_method::BB.find(name) == Solution_method::BB.end()){
        printf("get Requested element does not exist in the blackboard \n");
        return 0.;
    }

    return Solution_method::BB[name];
}

// write data identified by string var to blackboard data manager
//void blackboard::set(const char* var, double data, const int k/* = -1*/)
void Solution_method::set(std::string var, int data)
{
//    char name [255];
//    if (k >=0)
//        sprintf(name, "%s%d", var,k);
//    else
//        strcpy(name, var);

        Solution_method::BB[var] = data;
}



