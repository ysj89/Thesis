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
    ~Solution_method(){}

    virtual void getAction(Agent_H *m_Agent) = 0;

    //virtual void updateQtable(Agent *m_Agent, int _number_of_actions){}  // for current state, old state and reward

    virtual void updateQtable(Agent_H *m_Agent){}  // for current state, old state and reward

    virtual int getSizeQtable(){return 0;}

    //virtual std::unordered_map<std::string, ActionScoreMap> & getQtable(){std::unordered_map<std::string, ActionScoreMap> emptyMap; return emptyMap;}

};


/*
 * blackboard
 * Used to store all data for the Behaviour Tree to access
 * get() - returns the value in the blackboard with name "var"
 * 			for multiple entries with the same name k is used as an iterator
 * 			throws an error if element does not exist in list
 * set() - sets the value of the variable named "var"
 * 			if var is not in the list it is added
 * 			for multiple entries with the same name k is used as an iterator
 */
struct blackboard
{
public:
    blackboard()
    {
    }

    ~blackboard()
    {
//		for (std::map< std::string,  std::vector<double>* >::iterator it = BB.begin(); it != BB.end(); ++it)
//			delete it->second;
//		BB.clear();
    }

    double get(const char* var, const int k = -1);
    void set(const char* var, double data, const int k = -1);

private:
    std::unordered_map< std::string,  double > BB;
};

#endif // SOLUTION_METHOD_H
