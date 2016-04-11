#include "helpfunctions.h"

void Print::outputQTable(std::unordered_map<std::string, ActionScoreMap> Qtable, std::ostream &stream, char seperator)
{
    for(std::pair<std::string, ActionScoreMap> q : Qtable)
    {
        std::string &s = q.first;
        ActionScoreMap &m = q.second;
        for(std::pair<int, double> w : m)
        {
            int &a = w.first;
            double &v = w.second;
            stream << s << seperator << a << seperator << v << std::endl;
        }
    }
}


void Print::outputVectorPair(std::vector<std::pair<int,double> > VectorPair, std::ostream& stream, char seperator)
{
    for(std::pair<int, double> v : VectorPair)
    {
        int &ep = v.first;
        double &score = v.second;
        stream << ep << seperator << score << seperator << std::endl;
    }
}

void Print::outputUMstr2int(std::unordered_map<std::string, unsigned int> UM, std::ostream &stream, char seperator)
{
    for(std::pair<std::string, unsigned int> m : UM)
    {
        std::string &str = m.first;
        unsigned int &in = m.second;

        stream << str << seperator << in << std::endl;
    }
}
