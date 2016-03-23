#ifndef KHEPERA_AGENT_HEADING_H
#define KHEPERA_AGENT_HEADING_H



#include "posvec_struct.h"
#include "room.h"
#include "solution_method.h"
#include "helpfunctions.h"

typedef enum Action_heading
{
    TURN_RIGHT,
    TURN_LEFT
}Action_heading;

class Solution_method;

class Agent_H
{
public:
    Agent_H(Room *p_Room, int _START_X, int _START_Y, int _number_of_states, Solution_method *_sol_met, bool _savedata)
        :   sol_met(_sol_met),
            x_start(_START_X),
            y_start(_START_Y),
            savedata(_savedata),
            current_pos{_START_X, _START_Y},
            old_pos{_START_X, _START_Y},
            current_state(_number_of_states,0),
            old_state(_number_of_states,0)
        {
            this->m_Room = p_Room;

        StateVec current_state(_number_of_states,0);
        action = static_cast<Action_heading>(rand()%4);
        succes_probability = 0.9;
        }

    Room* m_Room;
    Action_heading action;
    Solution_method *sol_met;

    // Member variables
    int steps;
    int x_start, y_start;
    double succes_probability;
    double reward;
    double totalreward;
    bool savedata;
    PosVec current_pos;
    PosVec old_pos;

    StateVec current_state;
    StateVec old_state;

    std::vector<std::vector<double> > printMap;
    std::vector<std::vector<int>> positionPlot;


    // Member function
    void performAction();
    void runAgent(int _episodes, int _totalsteps);
    void printAgentinRoom(int filecount = 0);
    void printAgentReward(int filecount = 0);



};

#endif // KHEPERA_AGENT_HEADING_H
