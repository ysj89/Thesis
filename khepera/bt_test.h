#ifndef BT_TEST_H
#define BT_TEST_H

#include "bt_test.h"
#include "khepera_agent_heading.h"
#include "bt_structure.h"
#include "bt_composite.h"
#include "bt_conditions.h"
#include "bt_actions.h"

using namespace BT_Structure;

class Agent_H;

class BehaviorTree : public Solution_method
{
public:
    BehaviorTree() :
        check_for_wall_in_front(new Equal_to(3, -1)),
        action_turn_right(new Action_turn_right),
        action_move(new Action_move_forward),
        root(new Selector),
        sequence(new Sequence)
    {
        buildingTree();
    }

    ~BehaviorTree();

    virtual void getAction(Agent_H *m_Agent){}

private:
    // Conditions
    Equal_to* check_for_wall_in_front;
    // Actions
    Action_turn_right* action_turn_right;
    Action_move_forward* action_move;

    // Structure tree
    Selector* root;
    Sequence* sequence;


    void buildingTree();
    void runTree(Agent_H *m_Agent);


};

#endif // BT_TEST_H
