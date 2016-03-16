#include "khepera_agent.h"

void Agent::performAction()
{
    old_pos = current_pos;
    old_state = current_state;
    old_action = current_action;


    current_action = sol_met->getAction(current_state);

        // Probability of succesfull execution of action
            if ( (rand() % 100 + 1) / 100.0  < succes_probability)
            {
                    // Do nothing
            }
            else
            {
                current_action = static_cast<Action> ( rand()%4 );
            }



        // Perform action
            switch(current_action)
            {
            case UP:
                current_pos.y -= 1;
                break;
            case RIGHT:
                current_pos.x += 1;
                break;
            case DOWN:
                current_pos.y += 1;
                break;
            case LEFT:
                current_pos.x -= 1;
                break;


            default:
                std::cout << "\n Class:Agent :: Perform Action not implemented \n" ;
            }


        // Out of bound check
            while(current_pos.x < 0 )
            {
                current_pos.x = old_pos.x;
            }
            while(current_pos.y < 0 )
            {
                current_pos.y = old_pos.y;
            }
            while(current_pos.x > m_Room->x_size - 1)
            {
                current_pos.x = old_pos.x;
            }
            while(current_pos.y > m_Room->y_size -1)
            {
                current_pos.y = old_pos.y;
            }

        // Read sensors [empty, wall, trash]
            if(m_Room->worldMap[current_pos.x][current_pos.y] == 1)
            {

            }
            else
            {}



time = time + 1;

}


