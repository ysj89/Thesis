#ifndef KHEPERA_AGENT_HEADING_H
#define KHEPERA_AGENT_HEADING_H



#include "posvec_struct.h"
#include "room.h"
#include "solution_method.h"
#include "helpfunctions.h"

typedef enum Action_heading
{
    TURN_RIGHT,
    TURN_LEFT,
    MOVE_FORWARD
}Action_heading;


typedef enum Heading
{
    NORTH,
    EAST,
    SOUTH,
    WEST
}Heading;

class Solution_method;

class Agent_H
{
public:
    Agent_H(Room *p_Room, int _START_X, int _START_Y, Heading _PSI, int _number_of_states, int _number_of_actions, Solution_method *_sol_met, bool _savedata)
        :   heading(_PSI),
            sol_met(_sol_met),
            x_start(_START_X),
            y_start(_START_Y),
            num_act(_number_of_actions),
            savedata(_savedata),
            current_pos{_START_X, _START_Y},
            old_pos{_START_X, _START_Y},
            current_state(_number_of_states,0),
            old_state(_number_of_states,0)
        {
            this->m_Room = p_Room;

        StateVec current_state(_number_of_states,0);
        action = static_cast<Action_heading>(rand()%3);
        succes_probability = 1;

        explorationMap = std::vector<std::vector<int> > (m_Room->x_size, std::vector<int>(m_Room->y_size,0));

        }

    Room* m_Room;
    Action_heading action;
    Heading heading;
    Solution_method *sol_met;

    // Member variables
    int steps;
    int x_start, y_start;
    int num_act;
    int head, new_head;

    int sensor3x;
    int sensor3y;
    int sensor2x;
    int sensor2y;
    int sensor1x;
    int sensor1y;
    int sensor0x;
    int sensor0y;

    double succes_probability;
    double reward;
    double totalreward;
    bool savedata;
    PosVec current_pos;
    PosVec old_pos;

    StateVec current_state;
    StateVec old_state;

    std::vector<std::vector<double> > printMap;
    std::vector<std::vector<double> > printReward;
    std::vector<std::vector<int>> positionPlot;
    std::vector<std::vector<int>> explorationMap;


    // Member function
    void performAction();
    void runAgent(int _episodes, int _totalsteps);
    void printAgentinRoom(int filecount = 0);
    void printAgentExploration(int episode);
    void cleanExplorationMap();
    void printAgentReward(int filecount = 0);
    void printAgentRewardperEpisode(int episode_count);
    void checkBlockedSensor(int s0x, int s0y, int s1x, int s1y, int s2x, int s2y, int s3x, int s3y);



};

#endif // KHEPERA_AGENT_HEADING_H
