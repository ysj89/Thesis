#ifndef AGENT_H
#define AGENT_H
#include "taxiworld.h"
#include "iostream"
#include "position_struct.h"
//#include "solution_method.h"

class Solution_method;

typedef enum Action
{
    NORTH = 0,
    EAST,
    SOUTH,
    WEST,
    PICKUP,
    PUTDOWN,
    MAX_ACTIONS
}Action;

class Agent
{
public:
    Agent(TaxiWorld *p_World, int X_START, int Y_START)
        : m_World(NULL),
          x_start(X_START),
          y_start(Y_START)
    {

        if(p_World != NULL)
        {
            m_World = p_World;
        }

    }

    TaxiWorld* m_World;

    Solution_method* sol_met;

    int x_start, y_start;
    int x_goal = 4;
    int y_goal = 4;

    position pos = {x_start, y_start};

    Action action;
    int numberofstepstaken = 0;
    int numberofstepsallowed = 300;
    int numberofepisodesallowed = 5000;
    double succes_probability = 0.9;

    // Reward variable of the agent
    double reward;

    // Initializing functions
    void initializeAgent(int x, int y);

    // Performing action functions (dynamics)

    void chooseAction();
    void performAction();
    void setNumberofstepsallowed(int x);

    // Get to goal functions
    bool reachedGoal();

    // MASTER FUNCTION
    void setSolutionMethod(Solution_method* sol_met_agent);
    void runAgent();


};

#endif // AGENT_H
