//#include <cstdlib>
#include "random_action.h"


int Random_action::chooseAction(blackboard *BLKB)
{
    action = static_cast<Action_heading> ( rand()%3 );
    BLKB->set("action",action   );

    return action;
}
