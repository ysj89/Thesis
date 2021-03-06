#include "kheperaActions.h"

size_t KACTION = 3;       // total number of actions

namespace BT
{

enum BT_Status turn_right::update(blackboard *BLKB)
{
    BLKB->set("action",0);
    //std::cout << "BT_ACTION: action = turn_right " << std::endl;
    return BH_SUCCESS;
}

enum BT_Status turn_left::update(blackboard *BLKB)
{
    BLKB->set("action",1);
    //std::cout << "BT_ACTION: action = turn_left " << std::endl;
    return BH_SUCCESS;
}

enum BT_Status move::update(blackboard *BLKB)
{
    BLKB->set("action", 2);
    //std::cout << "BT_ACTION: action = move_forward " << std::endl;
    return BH_SUCCESS;
}


//enum BT_Status move1::update(blackboard *BLKB)
//{

//    BLKB->set("action", static_cast<int> ( vars[0] ) );
//    //std::cout << "BT_ACTION: action = " << vars[0] << std::endl;
//    return BH_SUCCESS;
//}


////////////////////////////////////////////////////////////////////////////////////////////
node* getAction(std::string action, std::vector<double> inputs /*= NULL*/)
{    

    node* task;
    if(inputs.empty())
    {
        if(action.compare("move") == 0)
            task = (node*) new move;
        else if(action.compare("turn_right") == 0)
            task = (node*) new turn_right;
        else if(action.compare("turn_left") == 0)
            task = (node*) new turn_left;
        else
            perror("Something is really wrong in :BT::Composite* getAction(std::string action, std::vector<double>* inputs)");
    }
    else{
        if (action.compare("move") == 0)
            task = (node*) new move;
        else if (action.compare("turn_right") == 0)
            task = (node*) new turn_right;
        else if (action.compare("turn_left") == 0)
            task = (node*) new turn_left;
        else
            perror("Something is really wrong in :BT::Composite* getAction(std::string action, std::vector<double>* inputs)");
    }




    return task;
}

// Add all actions to the if else if list below
node* getAction(size_t func /*= (size_t) - 1*/)
{
    node* task;
    switch (func)
    {
    case 0:
        task = (node*) new move();
        break;
    case 1:
        task = (node*) new turn_right();
        break;
    case 2:
        task = (node*) new turn_left();
        break;
    default:
        //std::cerr << "ERROR in getAction(unsigned int func): number of actions out of bounds"<<std::endl;
        return getAction( rand() % KACTION );
    }

//    task = (node*) new move1;

    return task;
}

}
