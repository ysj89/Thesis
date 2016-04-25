#include <algorithm>

#include "q_learning.h"



void Q_learning::getAction(Agent_H *m_Agent )
{
//    StateVec _state
    std::string str_state = vec2str(m_Agent->current_state);

    if (this->Qtable.find(str_state) == this->Qtable.end() )
    {
         //return static_cast<Action_heading>(rand() % 3); // return random action
         m_Agent->action = static_cast<Action_heading> (rand() % 3);
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
            m_Agent->action = static_cast<Action_heading> (rand() % 3);
            //return rand()% 3;
        }

//        return best_action;
        m_Agent->action = static_cast<Action_heading> (best_action);
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

//std::unordered_map<std::string, ActionScoreMap> &Q_learning::getQtable()
//{
//    return Qtable;
//}


