#ifndef CONDITIONS_H
#define CONDITIONS_H

#include "bt_structure.h"

namespace BT_Structure {


class Condition : public Node
{
public:
    Condition(int n_limit, int *n_var_pos)
        :limit(n_limit),
         var_pos(n_var_pos)
    {};

protected:
    int limit;      // Threshold
    int *var_pos;   // State (parameter) to be checked, must be reference for which state pos.x or pos.y

};

class Less_than : public Condition
{
public:
    Less_than(int m_limit, int *position)
        : Condition(m_limit, position)
        {};

    virtual enum Status update(Agent* P_AGENT) override
    {
        if (*var_pos < limit)
        {
            // cout << *var_pos << " is smaller than " << limit << endl; //FOR UNIT CHECKS
            return BH_SUCCES;
        }
        else
        {
            // cout << *var_pos << " is not smaller than " << limit << endl; //FOR UNIT CHECKS
            return BH_FAILURE;
        }
    };
};

class Greater_than : public Condition
{
public:
    Greater_than(int m_limit, int *position)
        : Condition(m_limit, position)
        {};

    virtual enum Status update(Agent* P_AGENT) override
    {
        if (*var_pos > limit)
        {
            // cout << *var_pos << " is smaller than " << limit << endl; //FOR UNIT CHECKS
            return BH_SUCCES;
        }
        else
        {
            // cout << *var_pos << " is not smaller than " << limit << endl; //FOR UNIT CHECKS
            return BH_FAILURE;
        }
    };
};

class Equal_to : public Condition
{
public:
    Equal_to(int m_limit, int * position)
        : Condition(m_limit, position)
    {};

    virtual enum Status update(Agent* P_AGENT) override
    {
        if (*var_pos == limit)
        {
            cout << *var_pos << " is equal to " << limit << endl;
            return BH_SUCCES;
        }

        else
        {
            cout << *var_pos << " is equal not to " << limit << endl;
            return BH_FAILURE;
        }

    };
};

class Not_equal_to : public Condition
{
public:
    Not_equal_to(int m_limit, int * position)
        : Condition(m_limit, position)
    {};

    virtual enum Status update(Agent* P_AGENT) override
    {
        if (*var_pos != limit)
        {
            // cout << *var_pos << " is equal to " << limit << endl;
            return BH_SUCCES;
        }

        else
        {
            // cout << *var_pos << " is equal not to " << limit << endl;
            return BH_FAILURE;
        }

    };
};


}
#endif // CONDITIONS_H
