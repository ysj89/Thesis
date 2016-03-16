#ifndef Q_LEARNING_H
#define Q_LEARNING_H

#include <unordered_map>

#include "solution_method.h"
#include "posvec_struct.h"

class Q_learning : public Solution_method
{
public:
    Q_learning(double ALPHA_, double GAMMA_, int number_of_states_, int battery_life_)
    :   Solution_method(),
        alpha(ALPHA_),
        gamma(GAMMA_)
    {




    }


    // Member variables
    int best_action;
    double alpha, gamma;



    std::vector<double>dummy;
    std::vector<double>::iterator max_q_value;
    std::unordered_map<std::string, ActionScoreMap> Qtable;

    // Member functions
    virtual Action getAction(StateVec _state ); // Short to reduce size
    virtual void SolutionMethodupdate(Agent *m_Agent); // for current state, old state and reward




};

#endif // Q_LEARNING_H

