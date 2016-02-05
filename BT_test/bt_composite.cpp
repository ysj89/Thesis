#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include "bt_structure.h"
#include "bt_composite.h"
#include "bt_door.h"

namespace BT_Structure
{

enum Status Selector::update()
{

//            for(;;)
//            {

//                Status s = (*m_currentChild)->tick();

//                if ( s!= BH_SUCCES)
//                {
//                    return s;
//                }

//                if (++m_currentChild == m_children.end())
//                {
//                    return BH_SUCCES;
//                }
//            }

    for (Node* child : getChildren())
    {  // The generic Selector implementation
        if (child->update())  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
            return BH_SUCCES;
    }
    return BH_FAILURE;  // All children failed so the entire run() operation fails.
}


enum Status Sequence::update()
{

//            for(;;)
//            {

//                Status s = (*m_current)->tick();

//                if ( s!= BH_SUCCES)
//                {
//                    return s;
//                }

//                if (++m_current == m_children.end())
//                {
//                    return BH_SUCCES;
//                }
//            }

    for (Node* child : getChildren())
    {  // The generic Sequence implementation.
        if (!child->update())  // If one child fails, then enter operation run() fails.  Success only results if all children succeed.
            return BH_FAILURE;
    }
    return BH_SUCCES;  // All children suceeded, so the entire run() operation succeeds.

}

}

