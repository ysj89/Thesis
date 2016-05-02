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
    delete sequence;
    delete action_turn_right;
    delete action_move;
}

int BehaviorTree::getAction()
{
    root->update();

}

void BehaviorTree::buildingTree()
{
    root->addChild(sequence);
    root->addChild(action_move);

    sequence->addChild(check_for_wall_in_front);
    sequence->addChild(action_turn_right);
}

void BehaviorTree::runTree()
{
    root->update();
}
