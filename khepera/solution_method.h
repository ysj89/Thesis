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
    {
//        BB["sensor0"] = 1;
//        BB["sensor1"] = 1;
//        BB["sensor2"] = 1;
//        BB["sensor3"] = 1;
//        BB["sensor4"] = 1;
//        BB["sensor5"] = 1;
//        BB["sensor6"] = 1;
//        BB["sensor7"] = 1;
//        BB["sensor8"] = 1;
//        BB["action"] = rand()%3;
    }
    ~Solution_method(){}


    virtual int getAction() = 0;

    virtual void updateQtable(Agent_H *m_Agent){}  // for current state, old state and reward

    virtual double getQtableincrement(Agent_H *m_Agent){return 0;}

    virtual int getSizeQtable(){return 0;}

    //virtual std::unordered_map<std::string, ActionScoreMap> & getQtable(){std::unordered_map<std::string, ActionScoreMap> emptyMap; return emptyMap;}

    double get(std::string var, const int k = -1);
    void set(std::string var, int data);

private:
    std::unordered_map< std::string,  int > BB;

};




#endif // SOLUTION_METHOD_H
