#include "bt_actions.h"

namespace BT_Structure {

enum Status Action_turn_right::update()
{
    //getAction(m_Agent);
    //cout << "Action right should be 1 and is: " << P_AGENT->action << endl;
    getAction();
    return BH_SUCCES;
}


int Action_turn_right::getAction()
{
    Solution_method::set("action", 0);
    return 0;
}



enum Status Action_move_forward::update()
{
    getAction();
    return BH_SUCCES;
}

int Action_move_forward::getAction()
{
        Solution_method::set("action", 2);
        return 2;

}




}
