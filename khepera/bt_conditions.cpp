#include "bt_conditions.h"

namespace BT_Structure {

enum Status Equal_to::update(blackboard *BLKB)
{

    //double data = BLKB->get(var.data());

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
