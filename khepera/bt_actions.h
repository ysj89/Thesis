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

    void getAction(Agent_H *m_Agent);
    virtual enum Status update(blackboard *BLKB) override;
};


class Action_move_forward : public Node
{
public:
    Action_move_forward()
    {};

//    int getAction(StateVec state){return 0;};
    void getAction(Agent_H *m_Agent);
    virtual enum Status update(blackboard *BLKB) override;


};




}

#endif // BT_ACTIONS_H
