#ifndef KHEPERA_AGENT_H
#define KHEPERA_AGENT_H

#include "posvec_struct.h"
#include "room.h"
#include "solution_method.h"

class Solution_method;

// Observable states
//          1
//      9   2   3
//      8 Agent 4
//      7   6   5
//      10 = batterylife



class Agent
{
public:
    Agent(Room *p_Room, int _START_X, int _START_Y, int _number_of_states, Solution_method *_sol_met)
        :   sol_met(_sol_met),
            current_pos{_START_X, _START_Y},
            old_pos{_START_X, _START_Y},
            current_state(_number_of_states,0),
            old_state(_number_of_states,0)
        {
            this->m_Room = p_Room;
        }

    Room* m_Room;
    Action current_action;
    Action old_action;
    Solution_method *sol_met;

    // Member variables
    int time;
    double succes_probability;
    double reward;
    PosVec current_pos;
    PosVec old_pos;

    StateVec current_state;
    StateVec old_state;

    // Member function
    void performAction();



};

#endif // KHEPERA_AGENT_H


