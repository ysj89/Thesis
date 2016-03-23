#include "q_learning.h"

int Q_learning::getAction(StateVec _state)
{
    std::string str_state = vec2str(_state);

    if (this->Qtable.find(str_state) == this->Qtable.end() )
    {
        return static_cast<Action>(rand() % 4); // return random action
    }
    else
    {
        ActionScoreMap a = this->Qtable[str_state];

        Score max_score;
//        Action best_action;
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
        // TODO: Implement epsilon-greedy !
        if( ((rand()% 100 + 1 ) / 100) > (1-epsilon))
        {
            std::cout << "A random action has been selected" << "\n";
            return rand()%4;
        }
        return best_action;
    }

}

void Q_learning::update(Agent *m_Agent)
{
    std::string str_state_current = vec2str(m_Agent->current_state);
    std::string str_state_old = vec2str(m_Agent->old_state);

    if (this->Qtable.find(str_state_old) == this->Qtable.end() )  // NOTE: CURRENT OR OLD STATE?
    {
        ActionScoreMap a;
        a[UP] = 0;
        a[DOWN] = 0;
        a[LEFT] = 0;
        a[RIGHT] = 0;
        Qtable[str_state_old] = a;
    }

    if (this->Qtable.find(str_state_current) == this->Qtable.end() )  // NOTE: CURRENT OR OLD STATE?
    {
        ActionScoreMap a;
        a[UP] = 0;
        a[DOWN] = 0;
        a[LEFT] = 0;
        a[RIGHT] = 0;
        Qtable[str_state_current] = a;
    }

        ActionScoreMap a = this->Qtable[str_state_current];
        Score max_score;
        Action best_action;

            for(std::unordered_map<int,Score>::iterator it=a.begin(); it != a.end(); it++)
            {
                if(it == a.begin())
                {
                    max_score = it->second;
                    best_action = static_cast<Action>(it->first);
                }

                if(it->second > max_score)  // NOTE: In case two same scores, returns first
                {
                    max_score = it->second;
                    best_action = static_cast<Action>(it->first);
                }
            }

        double &Qold = Qtable[str_state_old][m_Agent->action];  // NOTE: changed old_action to current_old
        double &Qmax = Qtable[str_state_current][best_action];

        double Qnew = (Qold + alpha * (m_Agent->reward + gamma*Qmax - Qold ));


        // Qtable[str_state_old][m_Agent->old_action] = Qnew;
        Qold = Qnew;
//            Qtable[str_state_old][m_Agent->old_action] = Qnew;

}
