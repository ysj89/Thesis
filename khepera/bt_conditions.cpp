#include "bt_conditions.h"

namespace BT_Structure {

enum Status Equal_to::update()
{

    //double data = BLKB->get(var.data());
    double sensor_val_d = Solution_method::get(sensor_val);

    if (sensor_val_d == limit)
    {
        std::cout << sensor_val_d << " is equal to " << limit << std::endl;
        return BH_SUCCES;
    }

    else
    {
        std::cout << sensor_val_d << " is equal not to " << limit << std::endl;
        return BH_FAILURE;
    }

}



}
