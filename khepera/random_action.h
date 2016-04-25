#ifndef RANDOM_ACTION_H
#define RANDOM_ACTION_H

#include "posvec_struct.h"
#include "solution_method.h"

class Random_action : public Solution_method

{
public:
    Random_action()
        : Solution_method()
    {}


    int action;

    virtual int getAction(StateVec _state, int _number_of_actions);
};

#endif // RANDOM_ACTION_H
