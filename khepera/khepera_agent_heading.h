#ifndef KHEPERA_AGENT_HEADING_H
#define KHEPERA_AGENT_HEADING_H

#include "posvec_struct.h"
#include "room.h"
#include "solution_method.h"
#include "helpfunctions.h"
#include "save_files.h"
#include "blackboard.h"

#define NUMBER_OF_SENSORS 8
#define NUMBER_OF_OBSERVATIONS 3

typedef enum Action_heading
{
    TURN_RIGHT,
    TURN_LEFT,
    MOVE_FORWARD
}Action_heading;


typedef enum Heading
{
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
}Heading;

class Solution_method;

class Agent_H
{
public:
    Agent_H(Room *p_Room, int _START_X, int _START_Y, Heading _PSI, int _number_of_states, int _number_of_actions,
            Solution_method *_sol_met, Solution_method *_sol_met_2, blackboard *p_BLKB, blackboard *p_BLKB2, bool _savedata, double EPSILON)
        :   heading(_PSI),
          sol_met(_sol_met),
          sol_met_test(_sol_met_2),
          BLKB(p_BLKB),
          BLKB2(p_BLKB2),
          x_start(_START_X),
          y_start(_START_Y),
          num_act(_number_of_actions),
          savedata(_savedata),
          current_pos{_START_X, _START_Y},
          old_pos{_START_X, _START_Y},
          current_state(_number_of_states,0),
          old_state(_number_of_states,0),
          epsilon_0(EPSILON)

    {
        this->m_Room = p_Room;
        StateVec current_state(_number_of_states,0);
        action = static_cast<Action_heading>(rand()%3);
        succes_probability = 0.8;
        explorationMap = std::vector<std::vector<int> > (m_Room->x_size, std::vector<int>(m_Room->y_size,0));

    }



    Action_heading action;
    Room* m_Room;
    Heading heading;
    Solution_method *sol_met;
    Solution_method *sol_met_test;
    Save save;
    blackboard *BLKB;
    blackboard *BLKB2;



    // Member variables
    int steps;
    int x_start, y_start;
    int num_act;
    int head, head_new;

    int sensor3x, sensor3y, sensor2x, sensor2y, sensor1x, sensor1y, sensor0x, sensor0y;

    double succes_probability;
    double reward;
    double totalreward;
    bool savedata;
    PosVec current_pos;
    PosVec old_pos;

    StateVec current_state;
    StateVec old_state;
    double epsilon;
    double epsilon_0;

private:
    std::vector<std::vector<double> > printMap;
    std::vector<std::vector<double> > printReward;
    std::vector<std::vector<int>> positionPlot;
    std::vector<std::vector<int>> *foo = new std::vector<std::vector<int>>;
    std::vector<std::vector<int>> explorationMap;
    std::vector<std::pair<int,double>> totalRewardVec;
    std::vector<double> *rewardVec  = new std::vector<double>;
    std::vector<double> *Qvalue = new std::vector<double>;
    std::vector<double> *Qvaluetotal = new std::vector<double>;
    std::vector<double> *Qincrement = new std::vector<double>;
    std::vector<int> *wall_vec = new std::vector<int>;
    std::vector<std::vector<int>> good_actions;

public:
    void runAgent(int _episodes, int _totalsteps);

private:
    void resetCurrentState();
    void performAction(int num_episode, int current_episode);
    int getAction_f();
    void setSensorInformation();
    void spawnApple(int x, int y);
    void printAgentExploration(int episode);
    void cleanExplorationMap();
    void checkBlockedSensor(int s0x, int s0y, int s1x, int s1y, int s2x, int s2y, int s3x, int s3y);

};

#endif // KHEPERA_AGENT_HEADING_H
