#include "bt_actions.h"

namespace BT_Structure {



enum Status Action_turn_right::update(blackboard *BLKB)
{
    //getAction(m_Agent);
    //cout << "Action right should be 1 and is: " << P_AGENT->action << endl;
    BLKB->set("action",0);
    return BH_SUCCES;
}


enum Status Action_move_forward::update(blackboard *BLKB)
{
    BLKB->set("action", 2);
    return BH_SUCCES;
}





}
