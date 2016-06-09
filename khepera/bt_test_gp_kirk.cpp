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
    delete selector2;
    delete equal_to1;
    delete equal_to_apple0;
    delete equal_to_apple1;
    delete equal_to_apple2;
    delete equal_to_apple3;

}

void bt_test_gp_kirk::buildingTree()
{
//    root->addChild(sequence1);
//    root->addChild(move1);

//    sequence1->addChild(equal_to1);
//    sequence1->addChild(turn_right1);

    //      root->addChild(sequence1);
    //      root->addChild(sequence2);
    //      root->addChild(turn_right1);


    //      sequence1->addChild(selector2);
    //      selector2->addChild(equal_to_apple3);
    //      selector2->addChild(equal_to_apple2);
    //      selector2->addChild(equal_to_apple1);
    //      selector2->addChild(equal_to_apple0);
    //      sequence1->addChild(move1);

    //      sequence2->addChild(equal_to1);
    //      sequence2->addChild(turn_right1);

      root->addChild(sequence1);
      root->addChild(sequence2);
      root->addChild(turn_right1);


      sequence1->addChild(selector2);
      selector2->addChild(equal_to_wall0);
      selector2->addChild(equal_to_wall1);
      selector2->addChild(equal_to_wall2);
      selector2->addChild(equal_to_wall3);
      sequence1->addChild(move1);

      sequence2->addChild(equal_to1);
      sequence2->addChild(turn_right1);

//    GP::filledRandBT(root,3);

//    save BT to file for SmartUAV
    BT::saveFile( "../../BT_saves/BT2.txt" , root);



}

int bt_test_gp_kirk::chooseAction(blackboard *BLKB)
{
      root->update(BLKB);
//    return 0;
}



}
