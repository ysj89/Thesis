#include "bt_test_gp_kirk.h"
#include "../BT/btFile.h"

namespace BT
{

bt_test_gp_kirk::~bt_test_gp_kirk()
{
    delete root;
    delete sequence1;
    delete move1;
    delete turn_right1;
    delete equal_to1;
}

void bt_test_gp_kirk::buildingTree()
{
//    root->addChild(sequence1);
//    root->addChild(move1);

//    sequence1->addChild(equal_to1);
//    sequence1->addChild(turn_right1);

    GP::filledRandBT(root,2);

    // save BT to file for SmartUAV
    BT::saveFile( "../BT_saves/BT" , root);


}

int bt_test_gp_kirk::chooseAction(blackboard *BLKB)
{
    root->update(BLKB);
    return 0;
}



}
