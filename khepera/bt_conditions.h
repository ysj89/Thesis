#ifndef BT_CONDITIONS_H
#define BT_CONDITIONS_H

#include "bt_structure.h"

namespace BT_Structure {


class Condition : public Node
{
public:
    Condition(int n_limit, int m_var_check)
        :limit(n_limit),
         var_check(m_var_check)
    {}

protected:
    int limit;      // Threshold
    int var_check;   // State (variable) to be checked, must be reference to sensor value

};


class Equal_to : public Condition
{
public:
    Equal_to(int m_limit, int check)
        : Condition(m_limit, check)
    {}

    virtual void getAction(Agent_H *m_Agent)  {}
    virtual enum Status update(blackboard *BLKB) override;



};



}


#endif // BT_CONDITIONS_H
