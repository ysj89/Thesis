#ifndef SOLUTION_METHOD_H
#define SOLUTION_METHOD_H

//#include "khepera_agent.h"
#include "khepera_agent_heading.h"
#include "posvec_struct.h"


//class Agent;
class Agent_H;

class Solution_method
{
public:
    Solution_method()
    {}

    virtual void getAction(Agent_H *m_Agent) = 0;

    //virtual void updateQtable(Agent *m_Agent, int _number_of_actions){}  // for current state, old state and reward

    virtual void updateQtable(Agent_H *m_Agent){}  // for current state, old state and reward

    virtual int getSizeQtable(){return 0;}

    //virtual std::unordered_map<std::string, ActionScoreMap> & getQtable(){std::unordered_map<std::string, ActionScoreMap> emptyMap; return emptyMap;}

    ~Solution_method(){}

};

#endif // SOLUTION_METHOD_H
