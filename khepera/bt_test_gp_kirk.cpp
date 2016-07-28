#include "bt_test_gp_kirk.h"
#include "../BT/btFile.h"

namespace BT
{

bt_test_gp_kirk::~bt_test_gp_kirk()
{
    delete root;
    delete sequence1;
//    delete turn_right1;
//    delete equal_to1;
//    delete selector2;
//    delete equal_to1;
//    delete equal_to_apple0;
//    delete equal_to_apple1;
//    delete equal_to_apple2;
//    delete equal_to_apple3;

}

void bt_test_gp_kirk::buildingTree()
{


//    root = BT::loadFile("../../BT_saves/BT_2016-06-30_16:32:28.txt");
//    root = BT::loadFile("../../BT_saves/BT_2016-06-30_18:21:46.txt");
//    root = BT::loadFile("../../BT_saves/BT_2016-06-30_18:41:26_prune.txt");
//    root = BT::loadFile("../../BT_saves/BT_2016-06-30_18:54:55.txt");
//    root = BT::loadFile("../../BT_saves/BT_2016-06-30_20:00:19.txt");
//    root = BT::loadFile("../../BT_saves/BT_2016-07-01_12:49:52.txt");
//    root = BT::loadFile("../../BT_saves/BT_2016-07-05_16:51:58.txt");


//    root = BT::loadFile("../../BT_saves/BT_2016-07-07_16:47:14.txt");  // GOOD TREE

//      root = BT::loadFile("../../BT_saves/BT_2016-07-07_21:18:07_prune.txt");  // 5000 gen BT
//    root = BT::loadFile("../../BT_saves/BT_2016-07-08_15:39:26_prune.txt"); // Perfect tree that gets all apples when it sees it
//    root = BT::loadFile("../../BT_saves/BT_2016-07-14_12:22:49.txt");

    root = BT::loadFile("../../BT_saves/BT_2016-07-25_14:48:38_prune_adjusted.txt");



//    root->addChild(sequence1);
//    root->addChild(sequence2);
//    root->addChild(sequence3);
//    root->addChild(move1);

//    sequence1->addChild(equal_to_wall3);
//    sequence1->addChild(turn_right1);

//    sequence2->addChild(equal_to_apple5);
//    sequence2->addChild(turn_right1);

//    sequence3->addChild(equal_to_apple7);
//    sequence3->addChild(turn_left1);





//    save BT to file for SmartUAV
//    BT::saveFile( "../../BT_saves/BT5.txt" , root);

}

int bt_test_gp_kirk::chooseAction(blackboard *BLKB)
{
      root->update(BLKB);
//    return 0;
}

}

//    root->addChild(sequence1);
//    root->addChild(move1);

//    sequence1->addChild(equal_to1);
//    sequence1->addChild(turn_right1);

//          root->addChild(sequence1);
//          root->addChild(sequence2);
//          root->addChild(turn_right1);


//          sequence1->addChild(selector2);
//          selector2->addChild(equal_to_apple3);
//          selector2->addChild(equal_to_apple2);
//          selector2->addChild(equal_to_apple1);
//          selector2->addChild(equal_to_apple0);
//          sequence1->addChild(move1);

//          sequence2->addChild(equal_to1);
//          sequence2->addChild(turn_right1);

//      root->addChild(sequence1);
//      root->addChild(sequence2);
//      root->addChild(turn_right1);


//      sequence1->addChild(selector2);
//      selector2->addChild(equal_to_wall0);
//      selector2->addChild(equal_to_wall1);
//      selector2->addChild(equal_to_wall2);
//      selector2->addChild(equal_to_wall3);
//      sequence1->addChild(move1);

//      sequence2->addChild(equal_to1);
//      sequence2->addChild(turn_right1);


//    root->addChild(sequence1);

//    sequence1->addChild(turn_left1);
//    sequence1->addChild(turn_right1);
//    sequence1->addChild(equal_to_free3);

//    root->addChild(move1);

//    root->addChild(sequence2);
//    sequence2->addChild(equal_to_free3);
//    sequence2->addChild(equal_to_free1);
//    sequence2->addChild((equal_to_apple3));
//    sequence2->addChild(equal_to_wall1);

