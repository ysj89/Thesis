#ifndef BT_ACTIONS_H
#define BT_ACTIONS_H


#include "bt_structure.h"
#include "bt_composite.h"

namespace BT_Structure {

class Action_turn_right : public Node
{
public:
    Action_turn_right()

    {};

    virtual enum Status update(Agent_H *P_AGENT) override
    {
        P_AGENT->action = TURN_RIGHT;

        //cout << "Action right should be 1 and is: " << P_AGENT->action << endl;

        return BH_SUCCES;
    }

};




}

#endif // BT_ACTIONS_H
