#ifndef SOLUTION_METHOD_H
#define SOLUTION_METHOD_H

//#include "khepera_agent.h"
#include "khepera_agent_heading.h"
#include "posvec_struct.h"
#include "blackboard.h"


class Agent_H;

class Solution_method
{
public:
    Solution_method()
    {}
    ~Solution_method(){}


    virtual int chooseAction(blackboard *BLKB) = 0;

    virtual void updateQtable(Agent_H *m_Agent){}  // for current state, old state and reward

    virtual double getQtableincrement(Agent_H *m_Agent){return 0;}

    virtual double getQvalue(Agent_H *m_Agent){return 0;}

    virtual int getSizeQtable(){return 0;}

    virtual double sumQvalues(){return 0;}

    //virtual std::unordered_map<std::string, ActionScoreMap> & getQtable(){std::unordered_map<std::string, ActionScoreMap> emptyMap; return emptyMap;}

};




#endif // SOLUTION_METHOD_H
