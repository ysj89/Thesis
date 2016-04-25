//#include <cstdlib>
#include "random_action.h"


int Random_action::getAction(StateVec _state, int _number_of_actions)
{
    action = static_cast<Action_heading> ( rand()%_number_of_actions );

    return action;
}
