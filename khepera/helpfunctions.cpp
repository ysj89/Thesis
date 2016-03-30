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
