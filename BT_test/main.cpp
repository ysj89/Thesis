#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include "bt_structure.h"
#include "bt_composite.h"
#include "bt_door.h"

using namespace BT_Structure;
using namespace BT_door;
/*

           Root
             |
             |
  Selector (only one of these children need to succeed)
       /             \
      /               \
     /                 \
Door is open?      Sequence (all of these children need to succeed)
(if door is                /           \
already open,             /             \
we are done)             /               \
                   Approach door      Open the door
                  (if this fails
                  then the door
                  cannot be opened)
*/


int main() {

    // General Tree structures
    Sequence *root = new Sequence; // (&pAgent1)
    Sequence *sequence1 = new Sequence;  // Note that root can be either a Sequence or a Selector, since it has only one child.
    Selector* selector1 = new Selector;  // In general there will be several nodes that are Sequence or Selector, so they should be suffixed by an integer to distinguish between them.

    // Door problem actions/conditions
    DoorStatus* doorStatus = new DoorStatus {BH_FAILURE, 5};  // The door is initially closed and 5 meters away.

    CheckIfDoorIsOpenTask* checkOpen = new CheckIfDoorIsOpenTask (doorStatus);
    ApproachDoorTask* approach = new ApproachDoorTask (doorStatus, false);
    OpenDoorTask* open = new OpenDoorTask (doorStatus);

    /*
    // Structure
    Selector* root = new Selector;
    Sequence* sequence1 = new Sequence;
    Sequence* sequence2 = new Sequence;
    Sequence* sequence3 = new Sequence;

    less_than* condition_1 = new less_than(8, & pos.x);
    Condition* condition_2 = new Condition(y,less_than);
    Condition* condition_3 = new Condition(x,y,equal);

    Action* action_right    = new Action(right,increment);
    Action* action_up       = new Action(up, increment);
    Action* action_left     = new Action(left, decrement);

    // Tree
    root->addChild(sequence1);
    root->addChild(sequence2);
    root->addChild(sequence3);

    sequence1->addChild(condition_1);
    sequence1->addChild(action_right);

    sequence2->addChild(condition_2);
    sequence2->addChild(action_up);

    sequence3->addChild(condition_3);
    sequence3->addChild(action_left);
    */

    // Tree
    root->addChild (selector1);

    selector1->addChild (checkOpen);
    selector1->addChild (sequence1);

    sequence1->addChild (approach);
    sequence1->addChild (open);

    while (!root->update())

        // If the operation starting from the root fails, keep trying until it succeeds.
        std::cout << "--------------------" << std::endl;
        std::cout << std::endl << "Operation complete.  Behaviour tree exited." << std::endl;
//      std::cin.get();

        return -1;
//      delete root;
}


