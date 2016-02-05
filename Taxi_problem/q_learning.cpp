#include "q_learning.h"
#include "taxiworld.h"
#include "iostream"
#include <algorithm>
#include <fstream>

Action Q_learning::getAction(position pos)
{
    action =  static_cast<Action> ( policy[pos.y][pos.x][pos.passenger]);

    return action;
}

void Q_learning::SolutionMethodupdate(position pos, double reward)
{
    Qupdate(pos,reward);
    PolicyUpdate(pos);
}

void Q_learning::SaveData(int x, int y)
{
    for(int k = 0; k < 2; k++)
    {
        for(int i = 0; i < y; i++) // y-size of grid
        {
            for(int j = 0; j < x; j++) // x-size of grid
            {
                std::cout << policy[i][j][k] << "\t";
            }   std::cout << "\n" ;
        };      std::cout << "\n";
    }           std::cout << "\n";
}

void Q_learning::Qupdate(position pos, double reward) // Updates for passenger-state !!!!!!!!!!!!
{
    //action_old  =  static_cast<Action> ( policy[pos.oldy][pos.oldx][pos.oldpassenger] );
    action_new  =  static_cast<Action> ( policy[pos.y][pos.x][pos.passenger]);
    Qold = Qvalues[pos.oldy][pos.oldx][pos.oldpassenger][action];
    Qnew = Qvalues[pos.y][pos.x][pos.passenger][action_new];
    Qvalue = (Qold + alpha * (reward + gamma*Qnew - Qold));
    Qvalues[pos.oldy][pos.oldx][pos.oldpassenger][action] = Qvalue;
    //std::cout << "This is the updated Qvalues: " << Qvalues[pos.oldy][pos.oldx][pos.oldpassenger][action] << std::endl;
}

void Q_learning::PolicyUpdate(position pos) // Updates for passenger-state !!!!!!!!!!!!
{
    for(int i = 0; i < 6; i++)
    {
        dummy.push_back(Qvalues[pos.oldy][pos.oldx][pos.oldpassenger][i]);
    }
    max = max_element(dummy.begin(), dummy.end());
    bestaction = distance(dummy.begin() , max);
    //std::cout << "The best action is: " << bestaction << std::endl;
    policy[pos.oldy][pos.oldx][pos.passenger] = bestaction;
    dummy.clear();
}

/*
void Q_learning::sumQvalues(std::vector<std::vector<std::vector<std::vector<double> > > > qValues)
{
    for(auto &n : qValues)
    {
        for ( auto &m : n)
        {
            for(auto &k : m)
            {
                sum_of_elements += k ;
            }
        }
    }

    std::cout << "\n" << sum_of_elements << std::endl;
}*/

