#include <cmath>


#include "../BT_leafs/conditions.h"

size_t KCOND = 1;         	//total number of conditions [1 = only equal too!]
size_t NUMBER_OF_VARS = 8;	// total number of variables


namespace BT
{

std::tuple<std::string,double,double,double> input ( int i )
{
    char buff[255];
    double threshold;
    double lower_lim;
    double upper_lim;

    if(i < 8)
    {
        sprintf(buff,"sensor%d",i);
        lower_lim = 0;
        upper_lim = 2;
    }
    else
    {
        std::cerr<<"check number of variables, requested: " << i << std::endl;
        sprintf(buff,"sensor");
        lower_lim = 0.;
        upper_lim = 1;
    }

    // Needs to produce 1 of 3 random options: for 0 = wall, 1 = free, 3 = apple
    threshold = rand() % ((int)round(upper_lim) - (int)round(lower_lim) + 1) + lower_lim;                // test for 100 discrete points on range [lower_lim, upper_lim]
    if(threshold == 1)
        threshold = 3;

    return std::make_tuple(buff, threshold, lower_lim, upper_lim);
}

// ***************************************************************
// ***************************************************************
// Add all conditions to the if else if list below

node* getCondition(std::string condition, std::string m_sensor, size_t var)
{
    node* task;
    if (condition.compare("less_than") == 0)
        task = (node*) new less_than("khepera", var);
    else if
        (condition.compare("greater_than") == 0)
                task = (node*) new greater_than("khepera", var);

    else
    {
        task = NULL;
        std::cerr << "Something is really wrong in :BT::node* getCondition(std::string condition)"<<std::endl;
    }

    return task;
}

node* getCondition(std::string condition, std::vector<double> inputs)
{
    node* task;
    if (condition.compare("less_than") == 0)
        task = (node*) new less_than("khepera", static_cast<size_t> (inputs[0]), inputs[1]);
    else if (condition.compare("greater_than") == 0)
        task = (node*) new greater_than("khepera", static_cast<size_t> (inputs[0]), inputs[1]);
    else if(condition.compare("equal_to") == 0)
        task = (node*) new equal_to("khepera", static_cast<size_t> (inputs[0]), inputs[1]);
    else
    {
        task = NULL;
        std::cerr << "Something is really wrong in :BT::node* getCondition(std::string condition, std::vector<double>* inputs)"<<std::endl;
    }
    return task;
}



// Add all conditions to the if else if list below
node* getCondition(std::string m_sensor /*=("sensor" + std::to_string(rand()%NUMBER_OF_SENSORS))*/ , size_t func /*= rand() % KCOND*/, size_t var /*= NUMBER_OF_VARS*/)
{
    node* task;
    switch (func)
    {
    case 0:
        task = (node*) new equal_to("khepera", var);
        break;
    case 1:
        task = (node*) new greater_than("khepera", var);
        break;
    case 2:
        task = (node*) new less_than("khepera", var);
        break;
    default:
        std::cerr << "ERROR in getCondition(unsigned int func): number of conditions out of bounds"<<std::endl;
    }
    return task;
}



node* getCondition(size_t func /* = rand() % KCOND*/, size_t var /*= rand()% NUMBER_OF_OBSERVATIONS*/)
{
    node* task;
    switch (func)
    {
    case 0:
        task = (node*) new equal_to("khepera", var);
        break;
    case 1:
        task = (node*) new less_than("khepera", var);
        break;
    case 2:
        task = (node*) new greater_than("khepera", var);
        break;
    default:
        std::cerr << "ERROR in getCondition(unsigned int func): number of conditions out of bounds"<<std::endl;
    }
    return task;
}


}
