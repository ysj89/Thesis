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
          sequence3(new sequence),
          move1(new move),
           equal_to_apple5(new equal_to("khepera", 5,3 )),
          equal_to_apple7(new equal_to("khepera", 7,3 )),
          equal_to_wall3(new equal_to("khepera",3,0)),
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
    sequence* sequence3;
    move* move1;
    equal_to* equal_to_apple5;
    equal_to* equal_to_apple7;
    equal_to* equal_to_wall3;
    turn_right* turn_right1;
    turn_left* turn_left1;

    // Member functions
    void buildingTree();
    virtual int chooseAction(blackboard *BLKB);

};


}

#endif // BT_TEST_GP_KIRK_H
