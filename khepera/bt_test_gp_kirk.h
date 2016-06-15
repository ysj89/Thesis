#ifndef BT_TEST_GP_KIRK_H
#define BT_TEST_GP_KIRK_H

#include "../BT/behaviour.h"
#include "../BT_leafs/conditions.h"
#include "../BT_leafs/kheperaActions.h"
#include "../BT/composites.h"
#include "blackboard.h"
#include "../EvolutionaryLearning/GP.h"


namespace BT
{

class bt_test_gp_kirk : public Solution_method
{
public:
    bt_test_gp_kirk(blackboard *p_BLKB)
        : BLKB(p_BLKB),
          root(new selector),
          sequence1(new sequence),
          sequence2(new sequence),
          selector2(new selector),
          equal_to1(new equal_to("khepera",3, 0)),
          equal_to_apple0(new equal_to("khepera", 0,3 )),
          equal_to_apple1(new equal_to("khepera", 1,3 )),
          equal_to_apple2(new equal_to("khepera", 2,3 )),
          equal_to_apple3(new equal_to("khepera", 3,3 )),
          equal_to_wall0(new equal_to("khepera",0,0)),
          equal_to_wall1(new equal_to("khepera",1,0)),
          equal_to_wall2(new equal_to("khepera",2,0)),
          equal_to_wall3(new equal_to("khepera",2,0)),
          equal_to_free0(new equal_to("khepera",0,1)),
          equal_to_free1(new equal_to("khepera",1,1)),
          equal_to_free3(new equal_to("khepera",3,1)),
          move1(new move),
        turn_right1(new turn_right),
        turn_left1(new turn_left)
    {
        buildingTree();
    }

    ~bt_test_gp_kirk();

    // Member variable
    blackboard* BLKB;

    composite* root;
    sequence* sequence1;
    sequence* sequence2;
    selector* selector2;
    equal_to* equal_to1;
    equal_to* equal_to_apple0;
    equal_to* equal_to_apple1;
    equal_to* equal_to_apple2;
    equal_to* equal_to_apple3;
    equal_to* equal_to_wall0;
    equal_to* equal_to_wall1;
    equal_to* equal_to_wall2;
    equal_to* equal_to_wall3;
    equal_to* equal_to_free0;
    equal_to* equal_to_free1;
    equal_to* equal_to_free3;
    move* move1;
    turn_right* turn_right1;
    turn_left* turn_left1;

    // Member functions
    void buildingTree();
    virtual int chooseAction(blackboard *BLKB);

};


}

#endif // BT_TEST_GP_KIRK_H
