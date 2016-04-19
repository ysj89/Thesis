#include "bt_windygrid.h"
#include "bt_structure.h"
#include "bt_composite.h"
#include "bt_conditions.h"
#include "bt_action.h"

using namespace BT_Structure;

void run_bt(Agent* BT_AGENT, bool bt_seq, bool bt_prio)
{
    Action_right* action_right  = new Action_right(1);
    Action_down* action_down    = new Action_down(1);
    Action_left* action_left    = new Action_left(1);

    if(bt_seq)
    {
    // Structure
    Selector* root = new Selector;
    Sequence* sequence1 = new Sequence;
    Sequence* sequence2 = new Sequence;
    Sequence* sequence3 = new Sequence;

    Less_than* condition_1 = new Less_than(7, &BT_AGENT->pos.y);

    Less_than* condition_21 = new Less_than(4,&BT_AGENT->pos.x);
    Less_than* condition_22 = new Less_than(9,&BT_AGENT->pos.y);

    Equal_to* condition_31 = new Equal_to(9, &BT_AGENT->pos.y);
    Less_than* condition_32 = new Less_than(5, &BT_AGENT->pos.x);



    // Building the Tree
    root->addChild(sequence1);
    root->addChild(sequence2);
    root->addChild(sequence3);
    root->addChild(action_left);

    sequence1->addChild(condition_1);
    sequence1->addChild(action_right);

    sequence2->addChild(condition_21);
    sequence2->addChild(condition_22);
    sequence2->addChild(action_right);

    sequence3->addChild(condition_31);
    sequence3->addChild(condition_32);
    sequence3->addChild(action_down);

    // Initialisation Agent
    //BT_AGENT->setSteps(30);
    BT_AGENT->setTimeStep(30);
    BT_AGENT->initializeAgent(3,0);

   while(!BT_AGENT->madeIt())
       {

       root->update(BT_AGENT);
       BT_AGENT->performAction();
       }
    }

    if(bt_prio)
    {
        // Structure
        Selector* root = new Selector;
        Sequence* sequence1 = new Sequence;
        Sequence* sequence2 = new Sequence;

        Greater_than* condition_11 = new Greater_than(4, &BT_AGENT->pos.x);
        Greater_than* condition_12 = new Greater_than(6, &BT_AGENT->pos.y);

        Less_than* condition_21 = new Less_than(9, &BT_AGENT->pos.y);

        root->addChild(sequence1);
        root->addChild(sequence2);
        root->addChild(action_down);

        sequence1->addChild(condition_11);
        sequence1->addChild(condition_12);
        sequence1->addChild(action_left);

        sequence2->addChild(condition_21);
        sequence2->addChild(action_right);

        // Initialisation Agent
        //BT_AGENT->setSteps(30);
        BT_AGENT->setTimeStep(30);
        BT_AGENT->initializeAgent(3,0);

        while(!BT_AGENT->madeIt())
            {

            root->update(BT_AGENT);

            BT_AGENT->performAction();

            }

    }

}
