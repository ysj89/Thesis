#ifndef KHEPERA_AGENT_H
#define KHEPERA_AGENT_H

#include "posvec_struct.h"
#include "room.h"


typedef enum Action
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
    MAX_ACTIONS
}Action;

class Agent
{
public:
    Agent(Room *p_Room, int START_X_, int START_Y_)
    :   x_start(START_X_),
        y_start(START_Y_)
        {

            if(p_Room != NULL)
            {
                this->m_Room = p_Room;
            }
         }

    Room* m_Room;
    Action action;

    // Member variables
    int x_start, y_start;
    int time;
    double succes_probability;
    PosVec current_pos = {x_start, y_start};
    PosVec old_pos;


    // Member function
    void performAction();


};

#endif // KHEPERA_AGENT_H


