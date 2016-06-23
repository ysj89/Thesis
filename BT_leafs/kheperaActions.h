#ifndef KHEPERAACTIONS_H
#define KHEPERAACTIONS_H

#include <stdlib.h>
#include "../BT/behaviour.h"
#include <cmath>

namespace BT{

node* getAction(std::string action, std::vector<double> inputs);
node* getAction(size_t func = (size_t) - 1);


struct turn_right : public node
{
        virtual enum BT_Status update(blackboard *BLKB) override;
        virtual int chooseAction(blackboard *BLKB){return 0;}

public:
    turn_right()
        : node("khepera","action","turn_right")
    {
        vars.push_back(0);
        vars_upper_lim.push_back(0);
        vars_lower_lim.push_back(0);
    }



};

struct turn_left : public node
{
public:
    turn_left()
        : node("khepera", "action", "turn_left")
    {
        vars.push_back(1);
        vars_upper_lim.push_back(1);
        vars_lower_lim.push_back(1);
    };

    virtual enum BT_Status update(blackboard *BLKB) override;
    virtual int chooseAction(blackboard *BLKB){return 0;}
};

struct move : public node
{
public:
    move()
        : node("khepera", "action", "move")
    {
        vars.push_back(2);
        vars_upper_lim.push_back(2);
        vars_lower_lim.push_back(2);
    };
    virtual enum BT_Status update(blackboard *BLKB) override;
    virtual int chooseAction(blackboard *BLKB){return 0;}
};


}
#endif // KHEPERAACTIONS_H
