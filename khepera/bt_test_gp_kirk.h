#ifndef BT_TEST_GP_KIRK_H
#define BT_TEST_GP_KIRK_H

#include "../BT/behaviour.h"
#include "../BT_leafs/conditions.h"
#include "../BT_leafs/kheperaActions.h"
#include "../BT/composites.h"
#include "blackboard.h"


namespace BT
{

class bt_test_gp_kirk
{
public:
    bt_test_gp_kirk(blackboard *p_BLKB)
        : BLKB(p_BLKB),
          root(new selector),
          sequence1(new sequence)
    {

        root->addChild(sequence1);
    }


    ~bt_test_gp_kirk();



    // Member variable
    blackboard* BLKB;

    composite* root;
    node* sequence1;

    // Member functions
    void buildingTree();




};


}

#endif // BT_TEST_GP_KIRK_H
