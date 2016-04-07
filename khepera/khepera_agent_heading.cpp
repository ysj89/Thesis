#include <sstream>

#include "khepera_agent_heading.h"
#include "khepera_agent.h"
#include "transitionmatrix.h"

void Agent_H::performAction()
{
    old_pos = current_pos;
    old_state = current_state;
    reward = 0;

    action = static_cast<Action_heading> ( sol_met->getAction(current_state, num_act));

        // Probability of succesfull execution of action
//            if ( (rand() % 100 + 1) / 100.0  > 1-succes_probability)
//            {
//                action = static_cast<Action_heading> ( rand()%num_act );
//            }

        // Perform action
            switch(action)
            {
            case TURN_LEFT:     // 0
                head = static_cast<int>(heading);
                new_head = head - 1;
                    if(new_head < 0)
                    {
                        new_head = 3;
                    }
                heading = static_cast<Heading>(new_head);
//                reward = -4;
                break;
            case TURN_RIGHT:    // 1
                head = static_cast<int>(heading);
                new_head = head + 1;
                    if(new_head > 3)
                    {
                        new_head = 0;
                    }
                heading = static_cast<Heading>(new_head);
//                reward = -4;
                break;
            case MOVE_FORWARD:

                if(heading == NORTH)
                    current_pos.x -= 1;
                if(heading == EAST)
                    current_pos.y += 1;
                if(heading == SOUTH)
                    current_pos.x += 1;
                if(heading == WEST) // 3
                    current_pos.y -= 1;

//                reward = -1;
                break;


            default:
                std::cout << "\n Class:Agent :: Perform Action not implemented \n" ;
            }

        // Wall check
            if(m_Room->worldMap[current_pos.x][current_pos.y] == 0) // NOTE: Agent hit a wall, returns to old position
            {
                current_pos = old_pos;
                reward = -10;
            }
            if(m_Room->worldMap[current_pos.x][current_pos.y] == 3) // NOTE: Agent found trash, automatically cleans it and picks it up
            {
                reward = 100;
                m_Room->worldMap[current_pos.x][current_pos.y] = 1;
            }

        // State

            switch(heading)
            {
            case NORTH: // 0

                sensor3x = current_pos.x - 1;
                sensor3y = current_pos.y    ;
                sensor2x = current_pos.x - 2;
                sensor2y = current_pos.y    ;
                sensor1x = current_pos.x - 3;
                sensor1y = current_pos.y    ;
                sensor0x = current_pos.x - 4;
                sensor0y = current_pos.y;

                checkBlockedSensor(sensor0x, sensor0y, sensor1x, sensor1y, sensor2x, sensor2y, sensor3x, sensor3y);

                current_state[4] = m_Room->worldMap[current_pos.x][current_pos.y + 1];
                current_state[6] = m_Room->worldMap[current_pos.x][current_pos.y - 1];


                current_state[5] = m_Room->worldMap[current_pos.x - 1][current_pos.y + 1];
                current_state[7] = m_Room->worldMap[current_pos.x - 1][current_pos.y - 1];

                current_state[8] = NORTH;

                break;
            case EAST: // 1

                sensor3x = current_pos.x;
                sensor3y = current_pos.y + 1;
                sensor2x = current_pos.x;
                sensor2y = current_pos.y + 2;
                sensor1x = current_pos.x;
                sensor1y = current_pos.y + 3;
                sensor0x = current_pos.x;
                sensor0y = current_pos.y + 4;

                checkBlockedSensor(sensor0x, sensor0y, sensor1x, sensor1y, sensor2x, sensor2y, sensor3x, sensor3y);


                current_state[4] = m_Room->worldMap[current_pos.x + 1][current_pos.y];
                current_state[5] = m_Room->worldMap[current_pos.x + 1][current_pos.y + 1];
                current_state[6] = m_Room->worldMap[current_pos.x - 1][current_pos.y];
                current_state[7] = m_Room->worldMap[current_pos.x - 1][current_pos.y + 1];

                current_state[8] = EAST;
                break;

            case SOUTH: // 2
                sensor3x = current_pos.x + 1;
                sensor3y = current_pos.y;
                sensor2x = current_pos.x + 2;
                sensor2y = current_pos.y;
                sensor1x = current_pos.x + 3;
                sensor1y = current_pos.y;
                sensor0x = current_pos.x + 4;
                sensor0y = current_pos.y;

                checkBlockedSensor(sensor0x, sensor0y, sensor1x, sensor1y, sensor2x, sensor2y, sensor3x, sensor3y);

                current_state[4] = m_Room->worldMap[current_pos.x][current_pos.y - 1];
                current_state[5] = m_Room->worldMap[current_pos.x + 1][current_pos.y - 1];
                current_state[6] = m_Room->worldMap[current_pos.x][current_pos.y + 1];
                current_state[7] = m_Room->worldMap[current_pos.x + 1][current_pos.y + 1];

                current_state[8] = SOUTH;

                break;

            case WEST: // 3

                sensor3x = current_pos.x;
                sensor3y = current_pos.y - 1;
                sensor2x = current_pos.x;
                sensor2y = current_pos.y - 2;
                sensor1x = current_pos.x;
                sensor1y = current_pos.y - 3;
                sensor0x = current_pos.x;
                sensor0y = current_pos.y - 4;

                checkBlockedSensor(sensor0x, sensor0y, sensor1x, sensor1y, sensor2x, sensor2y, sensor3x, sensor3y);


                current_state[4] = m_Room->worldMap[current_pos.x - 1][current_pos.y];
                current_state[5] = m_Room->worldMap[current_pos.x - 1][current_pos.y - 1];
                current_state[6] = m_Room->worldMap[current_pos.x + 1][current_pos.y];
                current_state[7] = m_Room->worldMap[current_pos.x + 1][current_pos.y - 1];

                current_state[8] = WEST;
                break;
        }
            explorationMap[current_pos.x][current_pos.y] = (explorationMap[current_pos.x][current_pos.y] + 1 );
            rewardVec->at(steps) = reward;
            steps = steps + 1;
            totalreward = totalreward + reward;
}


void Agent_H::setSensorInformation()
{
    double obserstatecolor = 4.2;
    printMap = m_Room->worldMap;
    printMap[current_pos.x][current_pos.y] = 5;

    if(heading == NORTH)
    {
        printMap[current_pos.x - 1][current_pos.y] = obserstatecolor;
        if((current_pos.x - 4 ) > 0)
        {
            printMap[current_pos.x - 4][current_pos.y] = obserstatecolor;
            printMap[current_pos.x - 3][current_pos.y] = obserstatecolor;
            printMap[current_pos.x - 2][current_pos.y] = obserstatecolor;
        }
        else if((current_pos.x - 3 ) > 0)
        {
            printMap[current_pos.x - 3][current_pos.y] = obserstatecolor;
            printMap[current_pos.x - 2][current_pos.y] = obserstatecolor;
        }
        else if((current_pos.x - 2 ) > 0)
        {
            printMap[current_pos.x - 2][current_pos.y] = obserstatecolor;
        }

    }
    if(heading == EAST)
    {
        printMap[current_pos.x - 0][current_pos.y + 1] = obserstatecolor;
        if((current_pos.y + 4 ) < m_Room->y_size)
        {
            printMap[current_pos.x - 0][current_pos.y + 4] = obserstatecolor;
            printMap[current_pos.x - 0][current_pos.y + 3] = obserstatecolor;
            printMap[current_pos.x - 0][current_pos.y + 2] = obserstatecolor;
        }
        else if((current_pos.y + 3 ) < m_Room->y_size)
        {
            printMap[current_pos.x - 0][current_pos.y + 3] = obserstatecolor;
            printMap[current_pos.x - 0][current_pos.y + 2] = obserstatecolor;
        }
        else if((current_pos.y + 3 ) < m_Room->y_size)
        {
            printMap[current_pos.x - 0][current_pos.y + 2] = obserstatecolor;
        }

    }
    if(heading == SOUTH)
    {
     printMap[current_pos.x + 1][current_pos.y] = obserstatecolor;

        if((current_pos.x + 4 ) < m_Room->x_size)
        {
            printMap[current_pos.x + 4][current_pos.y] = obserstatecolor;
            printMap[current_pos.x + 3][current_pos.y] = obserstatecolor;
            printMap[current_pos.x + 2][current_pos.y] = obserstatecolor;
        }
        else if((current_pos.x + 3 ) < m_Room->x_size)
        {
            printMap[current_pos.x + 3][current_pos.y] = obserstatecolor;
            printMap[current_pos.x + 2][current_pos.y] = obserstatecolor;
        }
        else if((current_pos.x + 2 ) < m_Room->x_size)
        {
            printMap[current_pos.x + 2][current_pos.y] = obserstatecolor;
        }


    }
    if(heading == WEST) // 3
    {
        printMap[current_pos.x - 0][current_pos.y - 1] = obserstatecolor;

        if((current_pos.y - 4 ) > 0)
        {
            printMap[current_pos.x - 0][current_pos.y - 4] = obserstatecolor;
            printMap[current_pos.x - 0][current_pos.y - 3] = obserstatecolor;
            printMap[current_pos.x - 0][current_pos.y - 2] = obserstatecolor;
        }
        else if((current_pos.y - 3 ) > 0)
        {
            printMap[current_pos.x - 0][current_pos.y - 3] = obserstatecolor;
            printMap[current_pos.x - 0][current_pos.y - 2] = obserstatecolor;
        }
        else if((current_pos.y - 3 ) > 0)
        {
            printMap[current_pos.x - 0][current_pos.y - 2] = obserstatecolor;
        }

    }
}

void Agent_H::cleanExplorationMap()
{
    for (int i = 0; i < m_Room->x_size; i++)
    {
        for(int j = 0; j < m_Room->y_size; j++)
        {
                explorationMap[i][j] = 0;
        }
    }
}

void Agent_H::checkBlockedSensor(int s0x, int s0y, int s1x, int s1y, int s2x, int s2y, int s3x, int s3y)
{
    sensor3x = s3x;
    sensor3y = s3y;
    sensor2x = s2x;
    sensor2y = s2y;
    sensor1x = s1x;
    sensor1y = s1y;
    sensor0x = s0x;
    sensor0y = s0y;

    if (m_Room->worldMap[sensor3x][sensor3y] == 0)
    {
        current_state[0] = 0;
        current_state[1] = 0;
        current_state[2] = 0;
        current_state[3] = 0;
    }
    else if(m_Room->worldMap[sensor2x][sensor2y] == 0)
    {
        current_state[0] = 0;
        current_state[1] = 0;
        current_state[2] = 0;
        current_state[3] = m_Room->worldMap[sensor3x][sensor3y];
    }
    else if(m_Room->worldMap[sensor1x][sensor1y] == 0)
    {
        current_state[0] = 0;
        current_state[1] = 0;
        current_state[2] = m_Room->worldMap[sensor2x][sensor2y];
        current_state[3] = m_Room->worldMap[sensor3x][sensor3y];
    }
    else
    {
        current_state[0] = m_Room->worldMap[sensor0x][sensor0y];
        current_state[1] = m_Room->worldMap[sensor1x][sensor0y];
        current_state[2] = m_Room->worldMap[sensor2x][sensor0y];
        current_state[3] = m_Room->worldMap[sensor3x][sensor0y];
    }
}



void Agent_H::runAgent(int _episodes, int _totalsteps)
{
    m_Room->initializeTrash(15);
    *rewardVec = std::vector<double>(_totalsteps);

    int size_TPM = 500;
    TransitionMatrix TM(size_TPM, num_act);

    for(int i = 0; i < _episodes; i++ )
    {
        current_pos = { x_start , y_start };
        steps = 0;
        totalreward = 0;
        reward = 0;
        m_Room->cleanWorldMap();
        m_Room->worldMap = m_Room->setMap;
        m_Room->worldMap[current_pos.x][current_pos.y + 2] = 3;
        printMap = m_Room->worldMap;
        printMap[x_start][y_start + 2] = 3;
        printMap[current_pos.x][current_pos.y] = 5;

            while(steps < _totalsteps)
            {
                performAction();
                sol_met->updateTransitionMatrix(current_state, old_state, action);

                if(i > _episodes/2)
                {
                    TM.increment(old_state, current_state, action);
                }

                if(i == _episodes - 1)
                {
                    if(savedata == 1)
                    {
                        setSensorInformation();
                        save.printAgentinRoom(steps, printMap);
                        save.printAgentReward(rewardVec);
                    }
                }
                sol_met->update(this, num_act);
            }
            if (i % 100 == 0)
            {
                totalRewardVec.push_back(std::pair<int,double> (i, totalreward));
                save.printAgentExploration(i,explorationMap);
            }
        cleanExplorationMap();
    }

    TM.calculateTPM(size_TPM, num_act);
//    save.printTPM(TM.TPM);
    save.printTPM3D(TM.TPM2);
    save.printAgentRewardperEpisode(totalRewardVec);
}




