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

    int getAction();
    virtual enum Status update() override;
};


class Action_move_forward : public Node
{
public:
    Action_move_forward()
    {};

//    int getAction(StateVec state){return 0;};
    int getAction();
    virtual enum Status update() override;


};




}

#endif // BT_ACTIONS_H
