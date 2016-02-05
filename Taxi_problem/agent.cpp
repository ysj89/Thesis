#include "iostream"
#include <assert.h>

#include "agent.h"
#include "q_learning.h"

//Agent::Agent()
//{

//}

void Agent::initializeAgent(int x, int y)
{
    pos.x = x;
    pos.y = y;
}

void Agent::performAction()
{
    pos.oldx = pos.x;
    pos.oldy = pos.y;

    action = sol_met->getAction(pos);

    if ( (rand() % 100 + 1) / 100.0  < succes_probability)
    {
        action = action;
    }
    else
    {
        action = static_cast<Action> ( rand()%6 );
    }


    switch(action)
    {
    case NORTH:
        pos.y -=1;
        reward = -1;
        break;
    case EAST:
        pos.x +=1;
        reward = -1;
        break;
    case SOUTH:
        pos.y +=1;
        reward = -1;
        break;
    case WEST:
        pos.x -=1;
        reward = -1;
        break;
    case PICKUP:
        if(pos.x == x_goal && pos.y == y_goal)
        {
            pos.passenger = 1;
            reward = reward + 20;
        }
        else
        {
            reward = -10;
        }
        break;
    case PUTDOWN:
        reward =-10;
        break;

    default:
        std::cout << "Class:Agent :: Perform Action not implemented \n" ;
    }

    // Check for boundaries
    while(pos.x < 0)
    {
        pos.x = pos.oldx;
    }
    while(pos.y < 0)
    {
        pos.y = pos.oldy;
    }
    while(pos.x > m_World->x_size - 1)
    {
        pos.x = pos.oldx;
    }
    while(pos.y > (m_World->y_size - 1))
    {
        pos.y = pos.oldy;
    }

    // Reward function
    //    if(pos.x == x_goal && pos.y == y_goal)
    //    {
    //        reward = reward + 2;
    //    }
    numberofstepstaken = numberofstepstaken + 1; //== a = a + 1;


}

void Agent::setNumberofstepsallowed(int x)
{
    numberofstepsallowed = x;

}

bool Agent::reachedGoal()
{

    if(pos.passenger == 1)
    {
        std::cout << "Agent:reachedGoal: Yes, we picked up the passenger, now what?" << std::endl;
        return true;
    }
    else if (numberofstepstaken > numberofstepsallowed)
    {
        std::cout << "Agent:reachedGoal: To much steps bro!" << std::endl;
        return true;
    }
    else
    {
        return false;
    }

    //    if(pos.x == x_goal && pos.y == y_goal)
    //    {
    //        std::cout << "Agent:reachedGoal: Yes, You made it! What are you waiting for? Move on!" << std::endl;
    //        return true;
    //    }
    //    else if(numberofstepstaken > numberofstepsallowed)
    //    {
    //        std::cout << "Agent:reachedGoal: Too bad, it took you too long. Go Home!" << std::endl;
    //        return true;
    //    }
    //    else
    //    {
    //        return false;
    //    }
}

void Agent::setSolutionMethod(Solution_method *sol_met_agent)
{
    sol_met = sol_met_agent;

}

void Agent::runAgent()
{
    for(int episodes = 0; episodes < numberofepisodesallowed; episodes++)
    {
        pos.x = 0;
        pos.y = 0;
        numberofstepstaken = 0;
        pos.passenger = 0;

        while(!reachedGoal())
        {
            performAction();
            sol_met->SolutionMethodupdate(pos, reward);
        }

        sol_met->SaveData(5,5);;
    }

}
