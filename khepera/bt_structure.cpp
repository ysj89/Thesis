#include "bt_structure.h"

namespace BT_Structure {

Status Node::tick(Agent_H* P_AGENT)
{
    // If node is not intialised, initialise!
    if (m_eStatus == BH_INVALID)
    {
        //onInitialise();
    }

    // Run node behavior
    m_eStatus = update(P_AGENT);
    return m_eStatus;


    if(m_eStatus != BH_RUNNING)
    {
        //onTerminate(m_eStatus);
        //m_eStatus = BH_INVALID;
    }

}


}
