#include <iostream>
#include <algorithm>

#include "windygridworld.h"
#include "agent.h"

using std::vector;
using namespace std;

// Idea- only make states from visited positions, doesn't need world information??

// Initialiazing the starting position of the agent
void Agent::initializeAgent(int x_pos, int y_pos)
{
    pos.x = x_pos;
    pos.y = y_pos;
}
// Initialiazing Q learning parameters
void Agent::setParameters(double alpha_, double gamma_)
{
    alpha = alpha_;
    gamma = gamma_;
}
// Set target function for Agent
void Agent::setTarget(int x_, int y_)
{
    x_goal = x_;
    y_goal = y_;
}
int Agent::getEpisodes()
{
    return episodes;
}
void Agent::setEpisodes(int e)
{
    episodes = e;
}
void Agent::setTimeStep(int t)
{
    steps = t;
}
void Agent::setTotalSteps(int t)
{
    totalsteps = t;
}
int Agent::getSteps()
{
    return steps;
}
int Agent::getTotalSteps()
{
    return totalsteps;
}

/*
* Perform action
*/
void Agent::performAction()
{
    pos.oldx = pos.x;
    pos.oldy = pos.y;



    // Probability that action selected is executed (90%)
    if ( (rand() % 100 + 1) / 100.0  < succes_probability)
    {
        action = action;
    }
    else
    {
        action = static_cast<Action> ( rand()%4 );
    }

    switch(action)
    {
    case UP:
           if (pos.x > 0)
            pos.x -=1;
        break;
    case RIGHT:
         if (pos.y < m_world->get_y_size() )
            pos.y += 1;
        break;
    case DOWN:
         if (pos.x < m_world->get_x_size())
            pos.x +=1;
         break;
    case LEFT:
          if (pos.y > 0)
            pos.y -= 1;
         break;
    case NORTHEAST:
        if (pos.y < m_world->get_y_size() && pos.x > 0)
            pos.y += 1;
            pos.x -= 1;
        break;
    case SOUTHEAST:
        if (pos.y < m_world->get_y_size() && pos.x < m_world->get_x_size())
            pos.y += 1;
            pos.x += 1;
        break;
    case SOUTHWEST:
        if (pos.y > 0 && pos.x < m_world->get_x_size())
            pos.y -= 1;
            pos.x += 1;
        break;
    case NORTHWEST:
        if (pos.y > 0 && pos.x > 0 )
            pos.x -= 1;
            pos.y -= 1;
        break;

    default:
        cout << "AGENT: Not implemented action \n" ;
    }

        // Subtract windfield
        pos.x -= m_world->windPattern[pos.y];

        // Resolve out of bound
        while (pos.x < 0){
            pos.x = 0;
        }
        while (pos.y < 0){
            pos.y = 0;
        }
        while (pos.x > ( m_world->get_x_size() - 1 ) ){
            pos.x = m_world->get_x_size() - 1;
        }
        while (pos.y >( m_world->get_y_size() - 1) ){
            pos.y = m_world->get_y_size() - 1;
        }

    if(pos.x == x_goal && pos.y == y_goal)
        {
            goalReached = true;
            reward = 1.0 ; // reward = 0.0 - 0.1*steps;
        }
    else
            goalReached = false;
            reward = -1.0 ; // reward = -1.0 - 0.1*steps;

    totalsteps = totalsteps + 1;

    // cout << "action: " << action << " and new position is: x=" << pos.x <<  " y=" << pos.y << "\n";

    new_action = policy[pos.x][pos.y];

}
/*
* Get the action with the maximum value for q
*/
void Agent::chooseAction()
{
    action = static_cast<Action>( policy[pos.x][pos.y] );
    //cout << "this is the action selected: " << action << endl;
}
/*
* Update Qvalue-table
*/
void Agent::Qupdate()
{
    Qold = QValues[action][pos.oldx][pos.oldy];
    Qnew = QValues[new_action][pos.x][pos.y];
    QValues[action][pos.oldx][pos.oldy] = (Qold + alpha*(reward + gamma*Qnew - Qold));
}

/*
* Update Policy-table -- LARGER DUMMY VECTOR FOR KINSMOVE
*/
void Agent::PolicyUpdate()
{
    if((rand() % 99 + 1) < epsilon)
        {
            policy[pos.x][pos.y] = rand() % 3 ;
            cout << "Update policy random action  " << policy[pos.x][pos.y] << "\n";
        }
        else
            {
                for(int i = 0; i < 4; i++) // Increase to < 8 for KINGSMOVE
                {
                    dummy.push_back((QValues[i][pos.oldx][pos.oldy]));
                }

                max = max_element(dummy.begin(), dummy.end());
                policy[pos.oldx][pos.oldy] = distance(dummy.begin(), max);
                dummy.clear();
            }
}

bool Agent::madeIt()
{
    if(pos.x == x_goal && pos.y == y_goal )
    {
        cout << "Yes, I made it!" << endl;
        //sumQvalues(QValues);
            return true;
    }

    else if(getTotalSteps() >= steps)
        {
            cout << "Total number of steps taken exceeds your limit ! \n";
            cout << "steps = " << getSteps() << "\n";
            return true;
        }
    else
        {
            return false;
    }
}


double Agent::sumQvalues(vector<vector<vector<double> > > vector_3D)
{
    for ( auto &n : vector_3D)
    {
        for (auto &m : n)
        {
            for (auto &k :m)
            {
                sum_of_elements += k;
            }
        }
    }
    std::cout << sum_of_elements << std::endl;
    return sum_of_elements;
}

















void Agent::printQvalues()
{
    for(int i=0; i < 4; i++)
    {
        cout << "Q values for action " << i  << "\n";

        for(unsigned int j=0; j < policy.size(); j++)
        {

            for(unsigned int k = 0; k < policy[i].size() ; k++)
            {
                cout << QValues[i][j][k] << "\t" ;
            } cout << "\n";
        } cout <<"\n";
    }
}

void Agent::printPolicy()
{
    cout << endl << "We made it!" << endl << endl;
    cout << "The last state was " << pos.x << " " << pos.y << "\n";

    cout << endl << "The policy is now: " << endl << endl;
        for(unsigned int i=0; i< policy.size(); i++)
        {
            for(unsigned int j=0; j < policy[i].size(); j++)
            {
                cout << policy[i][j] << "\t" ;
            }   cout <<"\n";
        }       cout << "\n";
}



