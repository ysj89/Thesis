#ifndef CONDITIONS_H
#define CONDITIONS_H

#include <stdlib.h>
#include <tuple>
#include "../BT/behaviour.h"
#define MAX_SIZE (size_t) - 1

extern size_t KCOND;				//total number of conditions
extern size_t NUMBER_OF_VARS;		// total number of input variables

namespace BT
{

std::tuple<std::string,double,double,double> input ( int i );

node* getCondition(std::string condition,  std::string m_sensor, size_t var = MAX_SIZE);
node* getCondition(std::string condition, std::vector<double> inputs);
//node* getCondition(std::string m_sensor = ("sensor" + std::to_string(rand()%NUMBER_OF_SENSORS)) , size_t func = rand() % KCOND, size_t var = MAX_SIZE);
node* getCondition(std::string m_sensor = ("sensor" + std::to_string(rand()%NUMBER_OF_SENSORS)), size_t func = rand() % KCOND, double value = rand()% NUMBER_OF_OBSERVATIONS);

class condition : public node
{
public:
    condition(std::string vehicle_name, std::string func_name, size_t param, double value)
        : node(vehicle_name, "condition", func_name),
          k_var(param),
		  limit(value)
	{
//        std::tuple<std::string,double,double,double> set = input( k_var );
//        var = std::get<0>(set);

//        vars.push_back(double(k_var));
//        vars_lower_lim.push_back(double(k_var));
//        vars_upper_lim.push_back(double(k_var));

//        vars.push_back(limit);
//        vars_lower_lim.push_back(std::get<2>(set));
//        vars_upper_lim.push_back(std::get<3>(set));
    }
    condition(std::string vehicle_name, std::string func_name, size_t param = MAX_SIZE)
        : node(vehicle_name, "condition",func_name )
    {
		if (param >= NUMBER_OF_VARS)
			k_var = rand() % NUMBER_OF_VARS;
		else
			k_var = param;

//		std::tuple<std::string,double,double,double> set = input( k_var );

//		var = std::get<0>(set);
//		limit = std::get<1>(set);

//		vars.push_back(double(k_var));
//        vars_lower_lim.push_back(double(k_var));
//		vars_upper_lim.push_back(double(k_var));

//        vars.push_back(limit);
//        vars_lower_lim.push_back(std::get<2>(set));
//		vars_upper_lim.push_back(std::get<3>(set));

    }
    condition(std::string vehicle_name, std::string func_name, double value)
        : node(vehicle_name, "condition", func_name),
        limit(value)
    {

    }

    size_t k_var;		// Parameter number
	std::string var;	// Parameter name
    double limit;		// threshold
};

class less_than : public condition
{
public:
    less_than(std::string vehicle_name, std::string m_sensor_val ,size_t param = MAX_SIZE)
        : condition(vehicle_name, "less_than", param)
    {
        var = m_sensor_val;
        vars.push_back(param);
    }

    less_than(std::string vehicle_name, size_t param, double value)
        : condition(vehicle_name, "less_than", param, value)
    {

    }
    less_than(std::string m_sensor_val, double value)
        : condition("khepera", "less_than", 1, value)
    {

    }

    BT_Status update(blackboard *BLKB)
    {

		double data = BLKB->get(var.data());
		if ( data < limit )
			return BH_SUCCESS;
		else
			return BH_FAILURE;
    }
};

class greater_than : public condition
{
public:
    greater_than(std::string vehicle_name, std::string m_sensor_val, size_t param = MAX_SIZE)
		: condition(vehicle_name, "greater_than", param)
    {
        var = m_sensor_val;
        vars.push_back(param);
    }
    greater_than(std::string vehicle_name, size_t param, double value)
        : condition(vehicle_name, "greater_than", param, value)
	{
    }
    greater_than(std::string m_sensor_val, double value)
        : condition("khepera", "greater_than", 1, value)
    {

    }

    BT_Status update(blackboard *BLKB)
    {
		double data = BLKB->get(var.data());
		if ( data > limit )
			return BH_SUCCESS;
		else
			return BH_FAILURE;
    }

    virtual int chooseAction(blackboard *BLKB)  {return 0;}
};



class equal_to : public condition
{
public:
    equal_to(std::string vehicle_name, std::string m_sensor_val, size_t param = MAX_SIZE)
        : condition(vehicle_name, "equal_to", param)
    {
        var = m_sensor_val;
        vars.push_back(param);
    }
    equal_to(std::string vehicle_name, std::string m_sensor_val, size_t param, double value)
        : condition(vehicle_name, "equal_to", param, value)
    {

    }
    equal_to(std::string m_sensor_val, double value)
        : condition("khepera", "equal_to", 1, value)
    {

    }

    BT_Status update(blackboard *BLKB)
    {
        double data = BLKB->get(var.data());
        if ( data == limit )
            return BH_SUCCESS;
        else
            return BH_FAILURE;
    }

    virtual int chooseAction(blackboard *BLKB)  {return 0;}
};

//class memory_set : public condition
//{
//public:
//	memory_set(std::string vehicle_name, size_t param = MAX_SIZE)
//		: condition(vehicle_name, "memory_set", param)
//    {
//    }
//    memory_set(std::string vehicle_name, size_t param, double value)
//        : condition(vehicle_name, "memory_set", param, value)
//	{
//    }

//    BT_Status update(blackboard *BLKB)
//    {
//		if ( BLKB->get("memory") ){
//			return BH_SUCCESS;
//		}
//		else{
//			return BH_FAILURE;
//		}

//    }
//};

}
#endif // CONDITIONS_H
