#ifndef AGENT_H
#define AGENT_H
#include <vector>
#include <iostream>

#include "windygridworld.h"

using namespace std;

// Action names
typedef enum Action
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
    NORTHEAST,
    SOUTHEAST,
    SOUTHWEST,
    NORTHWEST

}Action;

class Agent
{
public:
    // constructor for starting position of agent Default = (2,2) a = 0.8, gamma = 0.8, epsilon = 0.00 (random)
   Agent()
        :Agent(m_world, 2,2)
    {}
    Agent(WindyGridWorld* P_WORLD, int X_START, int Y_START)
        :Agent(P_WORLD, X_START, Y_START, 0.5, 0.9 , 0.0)
    {}
    Agent(WindyGridWorld* P_WORLD, int X_START, int Y_START, double ALPHA, double GAMMA, double EPSILON)
        :x_start(X_START),
         y_start(Y_START),
         alpha(ALPHA),
         gamma(GAMMA),
         epsilon(EPSILON)
    {

            if ( P_WORLD != NULL )
            {
                m_world = P_WORLD;
                int x_size = m_world->get_x_size();
                int y_size = m_world->get_y_size();

                policy = vector<vector<int> >{(unsigned) m_world->x_size,vector<int>(y_size,0)};

// Put random values in Policy (between 0 and 3)
                   for(int i=0; i< x_size; i++)
                   {
                      for(int j=0; j < y_size; j++)
                      {
                               policy[i][j] = rand()%4; // STANDARD MOVES [4] VS KINGSMOVE [8]
                                cout << policy[i][j] << "\t" ;
                      } cout <<"\n";
                   } cout << "\n";

                   // CHANGED 4 to 8 for KINSMOVE!
                    QValues = vector<vector<vector<double> > > (4, vector<vector<double> >(x_size, vector<double>(y_size , 0 ) ));

                    // Put random values in Q(a,s)-table
                    for(int i=0; i< 4; i++) //changed for KINGSMOVE
                    {
                    // cout << "Q(a,s) values for action " << i << "\n";
                        for(int j=0; j < x_size; j++)
                            {
                            for(int k = 0; k < y_size; k++)
                                {
                                 QValues[i][j][k] = rand()%100 / 100.0 ;
                                  cout << QValues[i][j][k] << "\t" ;
                                 }  cout << "\n";
                            }  cout <<"\n";
                     }
            }
            else
            {
                cout << "Throw error: class pointer empty";
            }

    }
    ~Agent(){}

    // The windygridwolrd in which this agent acts
    WindyGridWorld* m_world = NULL;

    // starting position on the grid (x and y) from the agent
    int x_start;
    int y_start;
    double succes_probability = 0.9;


    // Q-learning parameters
    double alpha, gamma, epsilon;
    vector<vector<vector<double> > > QValues;
    vector<vector<int> > policy;
    vector<double> dummy;

    Action action;

    int new_action;

    struct position_
    {
        int x;
        int y;
        int oldx;
        int oldy;
    };

    position_ pos = {x_start, y_start};

    // goal position on the grid (x and y)
    int x_goal = 4;
    int y_goal = 8;

    int increment;


    // Q learning variables
    double reward;
    double Qnew, Qold;
    bool goalReached = false;
    vector<double>::iterator max;

    vector<int> actionVector;

    //Variables
    int episodes, steps;
    int totalsteps = 0;

    double sum_of_elements;
    
    // Accessor function in class windygridworld
    void initializeAgent(int x_pos, int y_pos);
    void setParameters(double alpha, double gamma);
    void setTarget(int x_, int y_);

    // Performing action functions
    void chooseAction();
    void performAction();
    void Qupdate();
    void PolicyUpdate();
    bool madeIt();
    double sumQvalues(vector<vector<vector<double> > > vector_3D);

    // Get/Set functions for information out world
    int getEpisodes();                              // returns number of episodes the agent will run
    void setEpisodes(int e);                        // set the number of iterations
    void setTimeStep(int t);                        // set number of steps for 1 iteration
    int getSteps();                                 // get number of steps for simulation
    int getTotalSteps();                            // get total steps per episode
    void setTotalSteps(int t);                      // set max number of steps per episode

    void printQvalues();
    void printPolicy();
};
#endif // AGENT_H

