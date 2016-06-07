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
          equal_to1(new equal_to("khepera", 3, 0)),
          move1(new move),
        turn_right1(new turn_right)
    {
        buildingTree();
    }

    ~bt_test_gp_kirk();

    // Member variable
    blackboard* BLKB;

    composite* root;
    sequence* sequence1;
    equal_to* equal_to1;
    move* move1;
    turn_right* turn_right1;

    // Member functions
    void buildingTree();
    virtual int chooseAction(blackboard *BLKB);

};


}

#endif // BT_TEST_GP_KIRK_H
