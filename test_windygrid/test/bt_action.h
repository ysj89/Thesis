#ifndef BT_ACTION_H
#define BT_ACTION_H

#include "bt_structure.h"

namespace BT_Structure
{


class Action : public Node
{
public:
    Action(int n_increment)
        :increment(n_increment)
    {};
    // cout << "Action from BT evaluation is: " << P_AGENT->action << endl;
protected:
    int increment;      // stepsize for action


};

class Action_right : public Action
{
public:
    Action_right(int m_increment)
        :Action(m_increment)
    {};

    virtual enum Status update(Agent *P_AGENT) override
    {
        P_AGENT->action = RIGHT;

        //cout << "Action right should be 1 and is: " << P_AGENT->action << endl;

        return BH_SUCCES;
    }

};

class Action_left : public Action
{
public:
    Action_left(int m_increment)
        :Action(m_increment)
    {
    };

    virtual enum Status update(Agent *P_AGENT) override
    {
        P_AGENT->action = LEFT;
        //cout << "Action left show be 3 and is: " << P_AGENT->action << endl;
        return BH_SUCCES;
    }
};

class Action_up : public Action
{
public:
    Action_up(int m_increment)
        :Action(m_increment)
    {
    };

    virtual enum Status update(Agent *P_AGENT) override
    {
        P_AGENT->action = UP;
        // cout << "Action up should be 0 and is: " << P_AGENT->action << endl;
        return BH_SUCCES;
    }
};

class Action_down : public Action
{
public:
    Action_down(int m_increment)
        :Action(m_increment)
    {
    };

    virtual enum Status update(Agent *P_AGENT) override
    {
        P_AGENT->action = DOWN;
        //cout << "Action up should be 2 and is: " << P_AGENT->action << endl;
        return BH_SUCCES;
    }
};

}
#endif // BT_ACTION_H
