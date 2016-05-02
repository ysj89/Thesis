#include <algorithm>

#include "q_learning.h"



int Q_learning::getAction()
{

    std::vector<int> state_vec(9);

    state_vec[0] = Solution_method::get("sensor0");
    state_vec[1] = Solution_method::get("sensor1");
    state_vec[2] = Solution_method::get("sensor2");
    state_vec[3] = Solution_method::get("sensor3");
    state_vec[4] = Solution_method::get("sensor4");
    state_vec[5] = Solution_method::get("sensor5");
    state_vec[6] = Solution_method::get("sensor6");
    state_vec[7] = Solution_method::get("sensor7");
    state_vec[8] = Solution_method::get("sensor8");


    //std::string str_state = vec2str(m_Agent->current_state);
    std::string str_state = vec2str(state_vec);

    if (this->Qtable.find(str_state) == this->Qtable.end() )
    {
        Solution_method::set("action",rand()%3);
         return rand() %3;
    }
    else
    {
        ActionScoreMap a = this->Qtable[str_state];
        Score max_score;
        int best_action;

        for(std::unordered_map<int,Score>::iterator it=a.begin(); it != a.end(); it++)
        {
            if(it == a.begin())
            {
                max_score = it->second;
                best_action = static_cast<int>(it->first);
            }

            if(it->second > max_score)  // NOTE: In case two same scores, returns first
            {
                max_score = it->second;
                best_action = static_cast<int>(it->first);
            }
        }
        // TODO: Implement epsilon-greedy !
        if( ((rand()% 100 + 1 ) / 100) > (1-epsilon))
        {
            //std::cout << "A random action has been selected" << "\n";
            Solution_method::set("action",rand()%3);
            return rand()% 3;
        }

        Solution_method::set("action",best_action);


        return best_action;

    }
}

void Q_learning::updateQtable(Agent_H *m_Agent)  // Changed input for heading agent
{
    std::string str_state_current = vec2str(m_Agent->current_state);
    std::string str_state_old = vec2str(m_Agent->old_state);

    if (this->Qtable.find(str_state_old) == this->Qtable.end() )  // NOTE: CURRENT OR OLD STATE?
    {
        ActionScoreMap a;
        for(int i = 0; i <  m_Agent->num_act; i++)
        {
            a[i] = 0;
        }
        Qtable[str_state_old] = a;
    }

    if (this->Qtable.find(str_state_current) == this->Qtable.end() )  // NOTE: CURRENT OR OLD STATE?
    {
        ActionScoreMap a;

        for(int i = 0; i <  m_Agent->num_act; i++)
        {
            a[i] = 0;
        }

        Qtable[str_state_current] = a;
    }

        ActionScoreMap a = this->Qtable[str_state_current];
        Score max_score;
        int best_action;

            for(std::unordered_map<int,Score>::iterator it=a.begin(); it != a.end(); it++)
            {
                if(it == a.begin())
                {
                    max_score = it->second;
                    best_action = it->first;
                }

                if(it->second > max_score)  // NOTE: In case two same scores, returns first
                {
                    max_score = it->second;
                    best_action = it->first;
                }
            }

        double &Qold = Qtable[str_state_old][m_Agent->action];  // NOTE: changed old_action to current_old
        double &Qmax = Qtable[str_state_current][best_action];
        double Qnew = (Qold + alpha * (m_Agent->reward + gamma*Qmax - Qold ));


        // Qtable[str_state_old][m_Agent->old_action] = Qnew;
        //Qtable[str_state_old][m_Agent->old_action] = Qnew;
        Qold = Qnew;

}

int Q_learning::getSizeQtable()
{
    return Qtable.size();
}

double Q_learning::getQtableincrement(Agent_H *m_Agent)
{
    std::string str_state_current = vec2str(m_Agent->current_state);
    std::string str_state_old = vec2str(m_Agent->old_state);

    ActionScoreMap a = this->Qtable[str_state_current];
    Score max_score;
    int best_action;

        for(std::unordered_map<int,Score>::iterator it=a.begin(); it != a.end(); it++)
        {
            if(it == a.begin())
            {
                max_score = it->second;
                best_action = it->first;
            }

            if(it->second > max_score)  // NOTE: In case two same scores, returns first
            {
                max_score = it->second;
                best_action = it->first;
            }
        }

    double &Qold = Qtable[str_state_old][m_Agent->action];  // NOTE: changed old_action to current_old
    double &Qmax = Qtable[str_state_current][best_action];
    double Qnew = (Qold + alpha * (m_Agent->reward + gamma*Qmax - Qold ));


    // Qtable[str_state_old][m_Agent->old_action] = Qnew;
    //Qtable[str_state_old][m_Agent->old_action] = Qnew;
    double Qincrement = Qold - Qnew;

    return Qincrement;

}

//std::unordered_map<std::string, ActionScoreMap> &Q_learning::getQtable()
//{
//    return Qtable;
//}


