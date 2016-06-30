#include <algorithm>
#include "q_learning.h"


int Q_learning::chooseAction(blackboard *BLKB)
{
    getStateVec();

    std::string str_state = vec2str(state_vec);

    if (this->Qtable.find(str_state) == this->Qtable.end() )
    {

        BLKB->set("action",rand()%3);
        return rand() %3;
    }
    else
    {
        ActionScoreMap a = this->Qtable[str_state];
        Score max_score;
        int best_action;

        for(std::unordered_map<int,Score>::iterator it=a.begin(); it != a.end(); it++)
        {
            if(it == a.begin()){
                max_score = it->second;
                best_action = static_cast<int>(it->first);
            }

            if(it->second > max_score)  // NOTE: In case two same scores, returns first
            {
                max_score = it->second;
                best_action = static_cast<int>(it->first);
            }
        }

        // With probability epsilon selects a random action, and with probability (1 - epsilon) select a greedy action
        if( ((rand()% 100 + 1 ) / 100) > (1-epsilon))
        {
            //std::cout << "A random action has been selected" << "\n";
            BLKB->set("action",rand()%3);
            return rand()% 3;
        }

        BLKB->set("action",best_action);
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

        for(int i = 0; i <  m_Agent->num_act; i++){
            a[i] = 0;
        }
        Qtable[str_state_current] = a;
    }

    ActionScoreMap a = this->Qtable[str_state_current];
    Score max_score;
    int best_action;

    for(std::unordered_map<int,Score>::iterator it=a.begin(); it != a.end(); it++){
        if(it == a.begin()){
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

double Q_learning::getQvalue(Agent_H *m_Agent)
{
        std::string str_state_old = vec2str(m_Agent->old_state);
        ActionScoreMap a = this->Qtable[str_state_old];

        double score;
        score = a[m_Agent->action];

        return score;

}

double Q_learning::sumQvalues()
{
    double sum_of_elem;

    for(std::pair<std::string, ActionScoreMap> q : Qtable)
    {
        //std::string &s = q.first;
        ActionScoreMap &m = q.second;

        for(std::pair<int, double> w : m)
        {
            //int &a = w.first;
            //double &v = w.second;

            sum_of_elem += w.second;

        }
    }

    //std::cout << "Q-LEARNING:: sum of Qtable is: " << sum_of_elem << "\n";
    return sum_of_elem;
}

void Q_learning::getStateVec()
{
    state_vec[0] = BLKB->get("sensor0");
    state_vec[1] = BLKB->get("sensor1");
    state_vec[2] = BLKB->get("sensor2");
    state_vec[3] = BLKB->get("sensor3");
    state_vec[4] = BLKB->get("sensor4");
    state_vec[5] = BLKB->get("sensor5");
    state_vec[6] = BLKB->get("sensor6");
    state_vec[7] = BLKB->get("sensor7");
    //state_vec[8] = BLKB->get("sensor8");


}

//std::unordered_map<std::string, ActionScoreMap> &Q_learning::getQtable()
//{
//    return Qtable;
//}


