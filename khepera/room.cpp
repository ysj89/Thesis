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

void Room::setWall()
{
    for(int i = 0; i < x_size / 2; i++)
    {
        worldMap[i][y_size/2] = 1;
    }
}


void Room::initializeTrash() // TODO: Implement walls, trash cannot lie at a wall position
{
 for(int i = 0; i < 25; i++)
 {
     int xx = rand()% (x_size - 2) + 1;
     int yy = rand()% (y_size - 2) + 1;

     if(worldMap[xx][yy] != 1)
     {
         worldMap[xx] [yy] = 2;
     }

//     printWorldMap();
//     std::cout << "\n";
 }
}

void Room::setTrash()
{
    int xx = rand()% (x_size - 2) + 1;
    int yy = rand()% (y_size - 2) + 1;

    if(worldMap[xx][yy] != 1)
    {
        worldMap[xx] [yy] = 2;
    }
}
