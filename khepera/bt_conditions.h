#ifndef BT_CONDITIONS_H
#define BT_CONDITIONS_H

#include "bt_structure.h"

namespace BT_Structure {


class Condition : public Node
{
public:
    Condition(int n_limit, std::string m_sensor_val)
        :limit(n_limit),
          sensor_val(m_sensor_val)
    {}

protected:
    int limit;      // Threshold
    std::string sensor_val;   // State (variable) to be checked, must be reference to sensor value

};


class Equal_to : public Condition
{
public:
    Equal_to(int m_limit, std::string m_sensor_val)
        : Condition(m_limit, m_sensor_val)
    {}

    virtual int chooseAction(blackboard *BLKB)  {return 0;}
    virtual enum Status update(blackboard *BLKB) override;

};



}


#endif // BT_CONDITIONS_H
