#include "bt_composite.h"

//bt_composite::bt_composite()
//{

//}


namespace BT_Structure
{

enum Status Selector::update()
{
    for (Node* child : getChildren())
    {  // The generic Selector implementation
       // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.

        if (child->update())
            return BH_SUCCES;
    }
        return BH_FAILURE;  // All children failed so the entire run() operation fails.
}

enum Status Sequence::update()
{
    for (Node* child : getChildren())
    {   // The generic Sequence implementation.
        // If one child fails, then enter operation run() fails.  Success only results if all children succeed.

        if (!child->update())
            return BH_FAILURE;
    }
    return BH_SUCCES;  // All children suceeded, so the entire run() operation succeeds.

}

}
