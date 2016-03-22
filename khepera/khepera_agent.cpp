#include <sstream>

#include "khepera_agent.h"



void Agent::performAction()
{
    old_pos = current_pos;
    old_state = current_state;
    reward = 0;

    action = sol_met->getAction(current_state);

        // Probability of succesfull execution of action
            if ( (rand() % 100 + 1) / 100.0  > succes_probability)
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
            if(m_Room->worldMap[current_pos.x][current_pos.y] == 1) // NOTE: Agent hit a wall, returns to old position
            {
                current_pos = old_pos;
                reward = -1;
            }
            if(m_Room->worldMap[current_pos.x][current_pos.y] == 2) // NOTE: Agent found trash, automatically cleans it and picks it up
            {
                reward = 20;
                m_Room->worldMap[current_pos.x][current_pos.y] = 0;
                m_Room->setTrash();
            }


                                            // Observable states
                                            //       y1  y2  y3
                                            //  x0
                                            //  x1    7   0   1
                                            //  x2    6 Agent 2
                                            //  x3    5   4   3
                                            //  x4    8 = batterylife NOTE: not implemeted yet

        // Read sensors [empty, wall, trash]
            current_state[0] = m_Room->worldMap[current_pos.x - 1][current_pos.y    ];
            current_state[1] = m_Room->worldMap[current_pos.x - 1][current_pos.y + 1];
            current_state[2] = m_Room->worldMap[current_pos.x    ][current_pos.y + 1];
            current_state[3] = m_Room->worldMap[current_pos.x + 1][current_pos.y + 1];
            current_state[4] = m_Room->worldMap[current_pos.x + 1][current_pos.y    ];
            current_state[5] = m_Room->worldMap[current_pos.x + 1][current_pos.y - 1];
            current_state[6] = m_Room->worldMap[current_pos.x    ][current_pos.y - 1];
            current_state[7] = m_Room->worldMap[current_pos.x - 1][current_pos.y - 1];


    steps = steps + 1;
    totalreward = totalreward + reward;


}


void Agent::printAgentinRoom(int filecount)
{

    printMap = m_Room->worldMap;
    printMap[current_pos.x][current_pos.y] = 5;
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

void Agent::printAgentReward(int filecount)
{
    std::stringstream filename;
    filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation/Reward/reward" << filecount << ".txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputDouble(reward, fs);
    fs.close();
}



void Agent::runAgent(int _episodes, int _totalsteps)
{
    for(int i = 0; i < _episodes; i++ )
    {
        current_pos = { x_start , y_start };
        steps = 0;
        totalreward = 0;
        reward = 0;

            while(steps < _totalsteps)
            {
                performAction();

                if(savedata == 1)
                {
                    if(i == _episodes - 1)
                    {
                        printAgentinRoom(steps);
                        printAgentReward(steps);
                    }

                }
                sol_met->update(this);
                std::cout << "The reward was: " << reward << "\n";

            }
            std::cout << "This was episode: " << i << "\t with a total reward of: " << totalreward << "\n";
            }

}






