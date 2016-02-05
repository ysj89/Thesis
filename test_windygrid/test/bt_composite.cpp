#include <iostream>
#include <list>

#include "windygridworld.h"
#include "bt_composite.h"

namespace BT_Structure
{

enum Status Selector::update(Agent* P_AGENT)
{
    for (Node* child : getChildren())
    {  // The generic Selector implementation
       // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.

        if (child->update(P_AGENT))
            return BH_SUCCES;
    }
        return BH_FAILURE;  // All children failed so the entire run() operation fails.
}

enum Status Sequence::update(Agent* P_AGENT)
{
    for (Node* child : getChildren())
    {   // The generic Sequence implementation.
        // If one child fails, then enter operation run() fails.  Success only results if all children succeed.

        if (!child->update(P_AGENT))
            return BH_FAILURE;
    }
    return BH_SUCCES;  // All children suceeded, so the entire run() operation succeeds.




}


}



