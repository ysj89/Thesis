//#include <cstdlib>
#include "random_action.h"


int Random_action::getAction()
{
    action = static_cast<Action_heading> ( rand()%3 );

    return action;
}
