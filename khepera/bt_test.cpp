#include "khepera_agent_heading.h"
#include "bt_test.h"
#include "bt_structure.h"
#include "bt_composite.h"
#include "bt_conditions.h"
#include "bt_actions.h"

using namespace BT_Structure;

BehaviorTree::~BehaviorTree()
{
    delete root;
    delete sequence1;
    delete sequence2;
    delete sequence3;
    delete action_turn_right;
    delete check_apple_on_right;
    delete check_apple_on_right_front;
    delete check_for_wall_in_front;
    delete action_move;
}

int BehaviorTree::chooseAction(blackboard *BLKB)
{
    root->update(BLKB);
    return 0;
}

void BehaviorTree::buildingTree()
{
//    root->addChild(sequence1);
//    root->addChild(action_move);

//    sequence1->addChild(check_for_wall_in_front);
//    sequence1->addChild(action_turn_right);

    root->addChild(sequence1);
    root->addChild(sequence2);
    root->addChild(sequence3);
    root->addChild(action_move);

    sequence1->addChild(check_for_wall_in_front);
    sequence1->addChild(action_turn_right);

    sequence2->addChild(check_apple_on_right_front);
    sequence2->addChild(action_move);

    sequence3->addChild(check_apple_on_right);
    sequence3->addChild(action_turn_right);
}

void BehaviorTree::runTree(blackboard *BLKB)
{
    root->update(BLKB);
}
