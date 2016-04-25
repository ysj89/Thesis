#include "bt_conditions.h"

namespace BT_Structure {

enum Status Equal_to::update(Agent_H *m_Agent)
{
    if (var_check == limit)
    {
        std::cout << var_check << " is equal to " << limit << std::endl;
        return BH_SUCCES;
    }

    else
    {
        std::cout << var_check << " is equal not to " << limit << std::endl;
        return BH_FAILURE;
    }

}



}
