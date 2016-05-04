#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include<string>
#include<unordered_map>
/*
 * blackboard
 * Used to store all data for the Behaviour Tree to access
 * get() - returns the value in the blackboard with name "var"
 * 			for multiple entries with the same name k is used as an iterator
 * 			throws an error if element does not exist in list
 * set() - sets the value of the variable named "var"
 * 			if var is not in the list it is added
 * 			for multiple entries with the same name k is used as an iterator
 */
struct blackboard
{
public:
    blackboard()
    {
        BB["sensor0"] = 1;
        BB["sensor1"] = 1;
        BB["sensor2"] = 1;
        BB["sensor3"] = 1;
        BB["sensor4"] = 1;
        BB["sensor5"] = 1;
        BB["sensor6"] = 1;
        BB["sensor7"] = 1;
        BB["sensor8"] = 1;
        BB["action"] = 1;
    }

    ~blackboard()
    {
        //		for (std::map< std::string,  std::vector<double>* >::iterator it = BB.begin(); it != BB.end(); ++it)
        //			delete it->second;
        //		BB.clear();
    }

    double get(std::string var, const int k = -1);
    void set(std::string var, double data);

private:
    std::unordered_map< std::string,  double > BB;
};


#endif // BLACKBOARD_H
