#ifndef Q_LEARNING_H
#define Q_LEARNING_H

#include <unordered_map>
#include <tuple>

#include "solution_method.h"
//#include "posvec_struct.h"
#include "transitionmatrix.h"

class Q_learning : public Solution_method
{
public:
    Q_learning(double ALPHA_, double GAMMA_, double EPSILON_, int number_of_states_, int battery_life_, blackboard *p_BLKB)
    :   Solution_method(),
    BLKB(p_BLKB),
    alpha(ALPHA_),
    gamma(GAMMA_),
    epsilon(EPSILON_),
    state_vec(9)
    {
    }

    // Member variables
    blackboard *BLKB;

    //int best_action;
    int index;
    int counter = 0;
    double alpha, gamma, epsilon;

    std::vector<double>dummy;
    std::vector<double>::iterator max_q_value;
    std::vector<int> state_vec;

    std::unordered_map<std::string, ActionScoreMap> Qtable;


    // Member functions
    virtual int chooseAction(blackboard *BLKB);
    virtual void updateQtable(Agent_H *m_Agent); // for current state, old state and reward
    int getSizeQtable();
    double getQtableincrement(Agent_H *m_Agent);
    double getQvalue(Agent_H *m_Agent);
    double sumQvalues();
    //std::unordered_map<std::string, ActionScoreMap> & getQtable();

private:
    void getStateVec();
};

#endif // Q_LEARNING_H

