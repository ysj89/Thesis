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

    virtual enum Status update(blackboard *BLKB) override;
    virtual int chooseAction(blackboard *BLKB){return 0;}
};


class Action_move_forward : public Node
{
public:
    Action_move_forward()
    {};

    virtual int chooseAction(blackboard *BLKB){return 0;}
    virtual enum Status update(blackboard *BLKB) override;


};




}

#endif // BT_ACTIONS_H
