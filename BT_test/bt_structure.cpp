#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include "bt_structure.h"
#include "bt_composite.h"
#include "bt_door.h"

namespace BT_Structure {

Status Node::tick()
{
    // If node is not intialised, initialise!
    if (m_eStatus == BH_INVALID)
    {
        onInitialise();
    }

    // Run node behavior
    m_eStatus = update();

    return m_eStatus;
}

Status m_eStatus;
}


