#ifndef KHEPERA_AGENT_H
#define KHEPERA_AGENT_H

#include "posvec_struct.h"
#include "room.h"
#include "solution_method.h"

                    // Observable states
                    //     y0  y1  y2
                    // x0       0
                    // x1   8   1   2
                    // x2   7 Agent 3
                    // x3   6   5   4
                    //      9 = batterylife  NOTE: not implemented yet

class Solution_method;

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

        StateVec current_state(_number_of_states,0);
        }

    Room* m_Room;
    Action current_action;
    Action old_action;
    Solution_method *sol_met;

    // Member variables
    int steps;
    double succes_probability;
    double reward;
    double totalreward;
    PosVec current_pos;
    PosVec old_pos;

    StateVec current_state;
    StateVec old_state;

    // Member function
    void performAction();
    void runAgent(int _episodes, int _totalsteps);



};

#endif // KHEPERA_AGENT_H


