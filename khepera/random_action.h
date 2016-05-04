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

    virtual int chooseAction(blackboard *BLKB);
};

#endif // RANDOM_ACTION_H
