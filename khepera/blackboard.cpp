#include "blackboard.h"

double blackboard::get(std::string var, const int k /*= -1*/)
{

    std::string name;
    name = var;
    if (blackboard::BB.find(name) == blackboard::BB.end()){
        printf("get Requested element does not exist in the blackboard \n");
        return 0.;
    }

    return blackboard::BB[name];
}

void blackboard::set(std::string var, double data)
{
        blackboard::BB[var] = data;
}
