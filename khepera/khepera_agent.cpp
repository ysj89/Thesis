/*
#include <sstream>

#include "khepera_agent.h"

void Agent::performAction()
{
    old_pos = current_pos;
    old_state = current_state;
    reward = 0;

    action = static_cast<Action> ( sol_met->getAction(current_state, num_act));

        // Probability of succesfull execution of action
            if ( (rand() % 100 + 1) / 100.0  > 1-succes_probability/steps)
            {
                action = static_cast<Action> ( rand()%4 );
            }

        // Perform action
            switch(action)
            {
            case UP: // 0
                current_pos.x -= 1;
                break;
            case RIGHT: // 1
                current_pos.y += 1;
                break;
            case DOWN: // 2
                current_pos.x += 1;
                break;
            case LEFT: // 3
                current_pos.y -= 1;
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
                reward = 20;
                m_Room->worldMap[current_pos.x][current_pos.y] = 1;
                // m_Room->setTrash();
            }


            // Observable states
            //       y1  y2  y3                            y1  y2  y3
            //  x0                                   x0        0
            //  x1    7   0   1                      x1        1
            //  x2    6 Agent 2                      x2    7   2   3
            //  x3    5   4   3                      x3    6 Agent 4
            //  x4    8 = batterylife                x4        5


            int sensor0x = (current_pos.x - 3);
            int sensor0y = (current_pos.y);

            int sensor1x = (current_pos.x - 2);
            int sensor1y = (current_pos.y);

            int sensor2x = (current_pos.x - 1);
            int sensor2y = (current_pos.y);

            int sensor3x = (current_pos.x - 1);
            int sensor3y = (current_pos.y + 1);

            int sensor4x = (current_pos.x);
            int sensor4y = (current_pos.y + 1);

            int sensor5x = (current_pos.x + 1);
            int sensor5y = (current_pos.y);

            int sensor6x = (current_pos.x );
            int sensor6y = (current_pos.y - 1);

            int sensor7x = (current_pos.x - 1);
            int sensor7y = (current_pos.y - 1);


//            current_state[0] = m_Room->worldMap[current_pos.x - 1][current_pos.y    ];
//            current_state[1] = m_Room->worldMap[current_pos.x - 1][current_pos.y + 1];
//            current_state[2] = m_Room->worldMap[current_pos.x    ][current_pos.y + 1];
//            current_state[3] = m_Room->worldMap[current_pos.x + 1][current_pos.y + 1];
//            current_state[4] = m_Room->worldMap[current_pos.x + 1][current_pos.y    ];
//            current_state[5] = m_Room->worldMap[current_pos.x + 1][current_pos.y - 1];
//            current_state[6] = m_Room->worldMap[current_pos.x    ][current_pos.y - 1];
//            current_state[7] = m_Room->worldMap[current_pos.x - 1][current_pos.y - 1];

            if ((current_pos.x - 3 ) < 0)
            {
                current_state[0] = 0;
            }
            else
            {
                current_state[0] = m_Room->worldMap[sensor0x][sensor0y];
            }

            if ((current_pos.x - 2) < 0)
            {
                current_state[1] = 0;
            }
            else
            {
                current_state[1] = m_Room->worldMap[sensor1x][sensor1y];
            }



            current_state[2] = m_Room->worldMap[sensor2x][sensor2y];
            current_state[3] = m_Room->worldMap[sensor3x][sensor3y];
            current_state[4] = m_Room->worldMap[sensor4x][sensor4y];
            current_state[5] = m_Room->worldMap[sensor5x][sensor5y];
            current_state[6] = m_Room->worldMap[sensor6x][sensor6y];
            current_state[7] = m_Room->worldMap[sensor7x][sensor7y];


    steps = steps + 1;
    totalreward = totalreward + reward;


}


void Agent::printAgentinRoom(int filecount)
{

    int sensor0x = (current_pos.x - 3);
    int sensor0y = (current_pos.y);

    int sensor1x = (current_pos.x - 2);
    int sensor1y = (current_pos.y);

    int sensor2x = (current_pos.x - 1);
    int sensor2y = (current_pos.y);

    int sensor3x = (current_pos.x - 1);
    int sensor3y = (current_pos.y + 1);

    int sensor4x = (current_pos.x);
    int sensor4y = (current_pos.y + 1);

    int sensor5x = (current_pos.x + 1);
    int sensor5y = (current_pos.y);

    int sensor6x = (current_pos.x );
    int sensor6y = (current_pos.y - 1);

    int sensor7x = (current_pos.x - 1);
    int sensor7y = (current_pos.y - 1);

    double obserstatecolor = 4.2;
    printMap = m_Room->worldMap;
    printMap[current_pos.x][current_pos.y] = 5;
    if(sensor0x > 0)
    {
        printMap[sensor0x][sensor0y] = obserstatecolor;

    }
    if(sensor1x > 0)
    {
        printMap[sensor1x][sensor1y] = obserstatecolor;

    }
    printMap[sensor2x][sensor2y] = obserstatecolor;
    printMap[sensor3x][sensor3y] = obserstatecolor;
    printMap[sensor4x][sensor4y] = obserstatecolor;
    printMap[sensor5x][sensor5y] = obserstatecolor;
    printMap[sensor6x][sensor6y] = obserstatecolor;
    printMap[sensor7x][sensor7y] = obserstatecolor;



    std::stringstream filename;
    filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation/World/TotalWorld" << filecount << ".txt";

    std::ofstream fs;
    fs.open(filename.str(), std::ios::out); // IOS::OUT is vervangen vs IOS::APP
    Print::outputMatrix(printMap, fs);
    fs.close();

//    std::cout << "\n\n" ;
//    for(int i = 0; i < m_Room->x_size; i++)
//    {
//        for(int j = 0; j < m_Room->y_size; j++)
//        {
//            std::cout << printMap[i][j] << "\t";
//        }   std::cout << "\n" ;
//    }
//    std::cout << "\n" ;
//    std::cout << "Old position (x,y): " << old_pos.x << " " << old_pos.y << "\n";
//    std::cout << "Current position (x,y): " << current_pos.x << " " << current_pos.y << "\n";
//    std::cout << "The action performed was: " << action << " \n";

}

//void Agent::printAgentReward(int filecount)
//{
//    std::stringstream filename;
//    filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation/Reward/reward" << filecount << ".txt";
//    std::ofstream fs;
//    fs.open(filename.str(), std::ios::out);
//    Print::outputDouble(reward, fs);
//    fs.close();
//}



void Agent::runAgent(int _episodes, int _totalsteps)
{
    for(int i = 0; i < _episodes; i++ )
    {
        current_pos = { x_start , y_start };
        steps = 0;
        totalreward = 0;
        reward = 0;

        m_Room->cleanWorldMap();
        m_Room->initializeTrash(35);

            while(steps < _totalsteps)
            {
                performAction();

                if(savedata == 1)
                {
                    if(i == _episodes - 1)
                    {
                        printAgentinRoom(steps);
//                        printAgentReward(steps);
                    }

                }
                sol_met->updateQtable(this, num_act);
                // std::cout << "The reward was: " << reward << "\n";

            }
            std::cout << "This was episode: " << i << "\t with a total reward of: " << totalreward << "\n";
            }

}


*/





