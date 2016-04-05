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
//        TransitionMatrix = std::vector<std::vector<int> > (1, std::vector<int>(1,0));


    }

    // Member variables
    int best_action;
    int index;
    int counter = 0;
    double alpha, gamma, epsilon;

    std::vector<double>dummy;
    std::vector<double>::iterator max_q_value;
//    TransitionMatrix transitionMatrix;
    std::unordered_map<std::string, ActionScoreMap> Qtable;
//    std::unordered_map<std::string, int> string2intMap;

    // Member functions
    virtual int getAction(StateVec _state , int _number_of_actions);
    virtual void update(Agent_H *m_Agent, int _number_of_actions); // for current state, old state and reward
//    virtual void updateTransitionMatrix(StateVec state0, StateVec state1, int action);
};

#endif // Q_LEARNING_H

