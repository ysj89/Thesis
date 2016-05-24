#include "bt_test_gp_kirk.h"


namespace BT
{

bt_test_gp_kirk::~bt_test_gp_kirk()
{
    delete root;
    delete sequence1;
}

void bt_test_gp_kirk::buildingTree()
{
    root->addChild(sequence1, -1);
}




}
