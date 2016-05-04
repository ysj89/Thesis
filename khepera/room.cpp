#include "room.h"



void Room::setWalls()
{
    for(int j = 0; j < y_size; j++)
    {
        worldMap[0][j] = 0 ;
        worldMap[x_size-1][j] = 0; // Walls = 0
    }
    for(int i = 0; i < x_size; i++)
    {
        worldMap[i][0] = 0 ;
        worldMap[i][y_size-1] = 0;
    }
}

void Room::setWall()
{
    for(int i = 0; i < x_size / 2; i++)
    {
        worldMap[i][y_size/2] = 0; // Walls = 0
    }
}

void Room::setBlock()
{
    worldMap[(x_size/3)*2][(y_size/3)*2] = 0;
    worldMap[((x_size/3)*2)+1][(y_size/3)*2] = 0;
    worldMap[(x_size/3)*2][((y_size/3)*2) + 1] = 0;
    worldMap[((x_size/3)*2)+1][((y_size/3)*2)+1] = 0;
}


void Room::initializeTrash(int _num_of_trash) // TODO: Implement walls, trash cannot lie at a wall position
{
    int i = 0;
    while(++i < _num_of_trash)
    {
        int xx = rand()% (x_size - 2) + 1;
        int yy = rand()% (y_size - 2) + 1;

        if(worldMap[xx][yy] != 0)
        {
            worldMap[xx][yy] = 3;
        }
    }

    setMap = worldMap;
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


void Room::cleanWorldMap()
{
    for (int i = 0; i < x_size; i++)
    {
        for(int j = 0; j < y_size; j++)
        {
            if(worldMap[i][j] == 3)
            {
                worldMap[i][j] = 1;
            }

        }
    }
}

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

