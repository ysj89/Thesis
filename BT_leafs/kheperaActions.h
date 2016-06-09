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
//        var = "turn_right";
//        vars.push_back(0);
//        vars_upper_lim.push_back(2);
//        vars_lower_lim.push_back(0);
    }
//    turn_right(std::string func_name)
//        : node("khepera", "action", func_name)
//    {
//        vars.push_back(0);
//        vars_upper_lim.push_back(2);
//        vars_lower_lim.push_back(0);
//    }

        std::string var;	// Parameter name
};

struct turn_left : public node
{
public:
    turn_left()
        : node("khepera", "action", "turn_left")
    {
//        vars.push_back(1);
//        vars_upper_lim.push_back(0);
//        vars_lower_lim.push_back(2);
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
//        vars.push_back(2);
//        vars_upper_lim.push_back(0);
//        vars_lower_lim.push_back(2);
    };
    virtual enum BT_Status update(blackboard *BLKB) override;
    virtual int chooseAction(blackboard *BLKB){return 0;}
};



//// wheel speed randomly generated on interval [-0.5,0.5] with increments of 0.1
//struct wheelSpeed : public node
//{
//    BT_Status update(blackboard *BLKB);

//public:
//    wheelSpeed(double left, double right)
//        : node("khepera","action","wheelSpeed"),
//          leftWheelSpeed(left),
//          rightWheelSpeed(right)
//    {
//        vars.push_back(leftWheelSpeed);
//        vars_upper_lim.push_back(0.5);
//        vars_lower_lim.push_back(-0.5);

//        vars.push_back(rightWheelSpeed);
//        vars_upper_lim.push_back(0.5);
//        vars_lower_lim.push_back(-0.5);

//        if (std::fabs(leftWheelSpeed) > 0.5 || std::fabs(rightWheelSpeed) > 0.5)
//            std::cout<<"ACTION: "<<leftWheelSpeed<<" "<<rightWheelSpeed<<std::endl;
//    }

//    // (vars_upper_lim - vars_lower_lim)*(rand() % 21)/20. + vars_lower_lim
//    wheelSpeed()
//        : wheelSpeed((rand() % 101)/100. - 0.5, (rand() % 101)/100. - 0.5)
//    {}

//private:
//    double leftWheelSpeed;
//    double rightWheelSpeed;
//};


}
#endif // KHEPERAACTIONS_H
