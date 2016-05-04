#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <iostream>


class Room
{
public:
    Room()
        : Room(10,15)
    {}

    Room(const int x_, const int y_)
        : x_size(x_), y_size(y_)
    {
        worldMap = std::vector<std::vector<double> > (x_, std::vector<double>(y_,1));

        // Initialize world with walls
        setWalls();
        setWall();
        setBlock();

    };
    // X-size = number of row, Y-size number of colums (c++)
    int x_size;
    int y_size;

    std::vector<std::vector<double> > worldMap;
    std::vector<std::vector<double> > setMap;


    // Class members
    void printWorldMap();
    void cleanWorldMap();
    void setWalls();
    void setWall();
    void setBlock();
    void initializeTrash(int _num_of_trash);
    void setTrash();

    ~Room(){}
};




#endif // ROOM_H
