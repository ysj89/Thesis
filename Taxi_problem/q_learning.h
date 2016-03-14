#ifndef Q_LEARNING_H
#define Q_LEARNING_H

#include <vector>
#include <iostream>

#include "solution_method.h"

class Q_learning : public Solution_method
{
public:
    Q_learning()
    :   Q_learning(0.5, 0.9, 5, 5, 2, MAX_ACTIONS)
    {}

    Q_learning(double ALPHA, double GAMMA, int x_size, int y_size, int passenger, int number_of_actions)
    :   Solution_method(),
    alpha(ALPHA),
    gamma(GAMMA)
    {
            // HARD CODED SIZE OF GRID-WORLD
            //policy = std::vector<std::vector<int> >  { (unsigned ) y_size, std::vector<int>(x_size,0) };
            policy =    std::vector<std::vector<std::vector<int> > >
                        ( (unsigned ) y_size, std::vector<std::vector<int> >
                        (x_size,std::vector<int>
                        (passenger,0) ) );
            //Qvalues = std::vector<std::vector<std::vector<double> > > (y_size, std::vector<std::vector<double> >(x_size, std::vector<double>(number_of_actions,0)));

            Qvalues     = std::vector<std::vector<std::vector<std::vector<double> > > >
                        (y_size, std::vector<std::vector<std::vector<double> > >
                        (x_size, std::vector<std::vector<double> >
                        (passenger,std::vector<double>
                        (number_of_actions,0 ) ) ) );

            // Initialize Policy (random) - HARDCODED
            for(int i = 0; i < y_size; i++) // y-size of grid
            {
                for(int j = 0; j < x_size; j++) // x-size of grid
                {
                    for(int k = 0; k < passenger; k++) // passenger yes or no
                    {
                    policy[i][j][k] = rand()%number_of_actions; // number of actions

                    //std::cout << policy[i][j][k] << "\t";
                    }

                }   //std::cout << "\n" ;
            }; //std::cout << "\n";

            // Initialize random Q-values - HARDCODED
            for(int i = 0; i < y_size; i++) // y-size of grid-world
            {
                for(int j = 0; j< x_size; j++) // x-size of grid-world
                {
                    for(int k = 0; k < passenger; k++) // passenger yes or no
                    {
                        for(int l = 0; l < number_of_actions; l++) // number of possible actions
                        {
                        Qvalues[i][j][k][l] = rand()%100 / 100.0;
                        }
                    }
                }
            }
            /* // Check for Qvalues Q(state,action)
            for(int k = 0; k < 6; k++)
            {
                for(int i = 0; i < m_World->y_size; i++)
                {
                    for(int j = 0; j< m_World->x_size; j++)
                    {
                        std::cout << Qvalues[i][j][k] << "\t";
                    }   std::cout << "\n";
                }       std::cout << "\n";
            };*/


    }


    ~Q_learning(){}


    Action action;
    //Action action_old;
    Action action_new;

    // Q-learning variables
    double alpha, gamma;
    double Qnew, Qold, Qvalue;
    bool goalReached = false;
    int bestaction;


    std::vector<double>dummy;
    std::vector<double>::iterator max;
    double sum_of_elements;

    //std::vector<std::vector<std::vector<int> > >policy;
    //std::vector<std::vector<std::vector<std::vector<double> > > >Qvalues;

    std::vector<std::vector<std::vector<int> > >policy;
    std::vector<std::vector<std::vector<std::vector<double> > > >Qvalues;

    // Q-learning functions
    virtual Action getAction(position pos);
    virtual void SolutionMethodupdate(position pos, double reward);
    virtual void SaveData(int x, int y);

    void Qupdate(position pos, double reward);
    void PolicyUpdate(position pos);

    //void sumQvalues(std::vector<std::vector<std::vector<std::vector<double> > > > qValues);
};
#endif // Q_LEARNING_H
