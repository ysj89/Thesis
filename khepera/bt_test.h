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
    BehaviorTree(blackboard *p_BLKB) :
        BLKB(p_BLKB),
        check_for_wall_in_front(new Equal_to(0, "sensor3")),
        check_for_apple_in_front_s0(new Equal_to(3, "sensor0")),
        check_for_apple_in_front_s1(new Equal_to(3, "sensor1")),
        check_for_apple_in_front_s2(new Equal_to(3, "sensor2")),
        check_for_apple_in_front_s3(new Equal_to(3, "sensor3")),
        check_apple_on_right(new Equal_to(3,"sensor5")),
        check_apple_on_right_front(new Equal_to(3,"sensor4")),
        action_turn_right(new Action_turn_right),
        action_move(new Action_move_forward),
        root(new Selector),
        sequence1(new Sequence),
        sequence2(new Sequence),
        sequence3(new Sequence),
        selector1(new Selector)
    {
        buildingTree();
    }

    ~BehaviorTree();

    virtual int chooseAction(blackboard *BLKB);

    blackboard *BLKB;

public:
    // Conditions
    Equal_to* check_for_wall_in_front;
    Equal_to* check_for_apple_in_front_s0;
    Equal_to* check_for_apple_in_front_s1;
    Equal_to* check_for_apple_in_front_s2;
    Equal_to* check_for_apple_in_front_s3;
    Equal_to* check_apple_on_right;
    Equal_to* check_apple_on_right_front;
    // Actions
    Action_turn_right* action_turn_right;
    Action_move_forward* action_move;

    // Structure tree
    //Selector* root;
    CompositeNode* root;
    Sequence* sequence1;
    Sequence* sequence2;
    Sequence* sequence3;
    Selector* selector1;

    void buildingTree();
//    void runTree(blackboard *BLKB);


};

#endif // BT_TEST_H
