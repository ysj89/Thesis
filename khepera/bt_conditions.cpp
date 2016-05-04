#include "bt_conditions.h"

namespace BT_Structure {

enum Status Equal_to::update(blackboard *BLKB)
{

    //double data = BLKB->get(var.data());
    double sensor_val_d = BLKB->get(sensor_val);

    if (sensor_val_d == limit)
    {
        std::cout << sensor_val_d << " is equal to " << limit << std::endl;
        return BH_SUCCES;
    }

    else
    {
        std::cout << sensor_val_d << " is not equal to " << limit << std::endl;
        return BH_FAILURE;
    }

}



}
