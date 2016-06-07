#include "bt_actions.h"

namespace BT_Structure {



enum Status Action_turn_right::update(blackboard *BLKB)
{
    //getAction(m_Agent);
    //std::cout << "BT_ACTION: action = turn_right " << std::endl;
    BLKB->set("action",0);
    return BH_SUCCES;
}


enum Status Action_move_forward::update(blackboard *BLKB)
{
    BLKB->set("action", 2);
    //std::cout << "BT_ACTION: action = move_forward " << std::endl;
    return BH_SUCCES;
}





}
