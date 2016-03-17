#include "room.h"


void Room::printWorldMap()
{
    for(int i = 0; i < x_size; i++)
    {
        for(int j = 0; j < y_size; j++)
        {
            std::cout << worldMap[i][j] << "\t";
        }   std::cout << "\n" ;
    }
}

void Room::setWalls()
{
    for(int j = 0; j < y_size; j++)
    {
        worldMap[0][j] = 1 ;
        worldMap[x_size-1][j] = 1;
    }
    for(int i = 0; i < x_size; i++)
    {
         worldMap[i][0] = 1 ;
         worldMap[i][y_size-1] = 1;
    }


}


void Room::initializeTrash() // TODO: Implement walls, trash cannot lie at a wall position
{
 for(int i = 0; i < 25; i++)
 {
     worldMap[rand()% (x_size - 2) + 1] [rand()% (y_size - 2) + 1] = 2;
//     printWorldMap();
//     std::cout << "\n";
 }
}

void Room::setTrash()
{
    worldMap[rand()% (x_size - 2) + 1] [rand()% (y_size - 2) + 1] = 2;
}
