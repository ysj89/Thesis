#include "bt_actions.h"

namespace BT_Structure {

enum Status Action_turn_right::update(Agent_H *m_Agent)
{
    getAction(m_Agent);
    //cout << "Action right should be 1 and is: " << P_AGENT->action << endl;
    return BH_SUCCES;
}


void Action_turn_right::getAction(Agent_H *m_Agent)
{
    m_Agent->action = TURN_RIGHT;
}



enum Status Action_move_forward::update(Agent_H *m_Agent)
{
    m_Agent->action = MOVE_FORWARD;
    return BH_SUCCES;
}
void Action_move_forward::getAction(Agent_H *m_Agent)
{
    m_Agent->action = MOVE_FORWARD;
}


}
