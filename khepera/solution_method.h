#ifndef SOLUTION_METHOD_H
#define SOLUTION_METHOD_H

#include "khepera_agent.h"
#include "khepera_agent_heading.h"
#include "posvec_struct.h"

class Agent;
class Agent_H;

class Solution_method
{
public:
    Solution_method()
    {}

    virtual int getAction(StateVec state) = 0;
    virtual void update(Agent *m_Agent){}  // for current state, old state and reward
    virtual void update(Agent_H *m_Agent){}  // for current state, old state and reward


//    virtual void SaveData(int x, int y){};


    ~Solution_method(){}

};

#endif // SOLUTION_METHOD_H
