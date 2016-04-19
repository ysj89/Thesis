#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>

#include "windygridworld.h"
#include "agent.h"
#include "bt_conditions.h"
#include "bt_action.h"
#include "bt_structure.h"
#include "bt_composite.h"
#include "bt_windygrid.h"
#include "rl_sarsa.h"
#include "test.h"

using namespace std;
using namespace BT_Structure;

// To know when Q-table is converged, summing up the Q-values
double sum_of_elements;
double sumvector(vector<vector<vector<double> > > test)
{
    for ( auto &n : test)
    {
        for (auto &m : n)
        {
            for (auto &k :m)
            {
                sum_of_elements += k;
            }
        }
    }

    std::cout << "\n" << sum_of_elements << std::endl;
    return sum_of_elements;
}


int main()
{

    // Set objects
    WindyGridWorld World(7,10);            // initialize windygridworld
    Agent Agent1(&World , 3 , 0);          // initialize agent (start, alpha, gamma, epsilon)

    //Agent Agent2();
    //WindyGridWorld* pWorld = &World;
    Agent* pAgent1 = &Agent1;

    // RUN TEST
    //run_test(pAgent1);

    // Run Sarsa-algorithm and/or Behavior Tree
    run_sarsa(pAgent1);
    run_bt(pAgent1,0,1);


    //std::vector<std::vector<double> > dummy;
    vector<vector<vector<double> > > dummy;

    for(int i = 0; i < 2; i++)
    {
        std::vector<std::vector<double> > temp;

        for(int j = 0; j < 2; j++)
        {
            std::vector<double> temp2;

            for(int k = 0; k < 4; k++)
            {

                temp2.push_back( rand()%100);

            }

            temp.push_back(temp2);
        }

        dummy.push_back(temp);
        std::cout << "\n" ;
    };




    sumvector(dummy);

    return 0;

}

