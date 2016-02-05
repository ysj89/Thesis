#ifndef SOLUTION_METHOD_H
#define SOLUTION_METHOD_H
#include "iostream"

#include "position_struct.h"
#include "agent.h"



class Solution_method
{
public:

    Solution_method()
    {}

    virtual Action getAction(position pos) = 0;
    virtual void SolutionMethodupdate(position pos, double reward){};
    virtual void SaveData(int x, int y){};

    //virtual void update(position pos, double reward);

    ~Solution_method(){}

};



#endif // SOLUTION_METHOD_H
