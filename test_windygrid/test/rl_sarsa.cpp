#include "rl_sarsa.h"

void run_sarsa(Agent *P_AGENT)
{
    P_AGENT->setEpisodes(30000);            // set number of episodes
    P_AGENT->setTimeStep(100);              // set numer of steps per episode

     for (int e = 0; e < P_AGENT->getEpisodes(); e++)
     {

        P_AGENT->setTotalSteps(0);
        P_AGENT->initializeAgent(rand()%7,rand()%10);


        while(!P_AGENT->madeIt())
            {
            // Choose action
            P_AGENT->chooseAction();

            // Perform action in the grid and learn from it (update q value and policy)
            P_AGENT->performAction();
            P_AGENT->Qupdate();
            P_AGENT->PolicyUpdate();
            // pAgent1->actionVector.push_back(pAgent1->action);

            }

       // pAgent1->actionVector.clear();
     }
     P_AGENT->printQvalues();
     P_AGENT->printPolicy();
     // Save/display policy to check answer
}
