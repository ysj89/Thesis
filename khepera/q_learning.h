#ifndef Q_LEARNING_H
#define Q_LEARNING_H

#include <unordered_map>
#include <tuple>

#include "solution_method.h"
#include "posvec_struct.h"
#include "transitionmatrix.h"

class Q_learning : public Solution_method
{
public:
    Q_learning(double ALPHA_, double GAMMA_, double EPSILON_, int number_of_states_, int battery_life_)
    :   Solution_method(),
        alpha(ALPHA_),
        gamma(GAMMA_),
        epsilon(EPSILON_)
    {
    }

    // Member variables
    int best_action;
    int index;
    int counter = 0;
    double alpha, gamma, epsilon;

    std::vector<double>dummy;
    std::vector<double>::iterator max_q_value;

    std::unordered_map<std::string, ActionScoreMap> Qtable;


    // Member functions
    virtual int getAction(StateVec _state , int _number_of_actions);
    virtual void update(Agent_H *m_Agent, int _number_of_actions); // for current state, old state and reward
    int getSizeQtable();
};

#endif // Q_LEARNING_H

