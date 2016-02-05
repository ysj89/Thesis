#ifndef WINDYGRIDWORLD_H
#define WINDYGRIDWORLD_H
//#pragma once // <- wtf deed dit hier?


class WindyGridWorld
{
public:

    // constructor for 0 to 2 inputs - 0 input generates a random x (1-10) and y (1-7) position
    WindyGridWorld()
        : WindyGridWorld(7,10)
    {}
//    WindyGridWorld(int X_START)
//    {
//        x_start = X_START;
//        y_start = 7;
//    }
    WindyGridWorld(int X_SIZE)
        :WindyGridWorld(X_SIZE,10)
    {}

    WindyGridWorld(int X_SIZE, int Y_SIZE)
        : x_size(X_SIZE),
          y_size(Y_SIZE)
    {
//        x_size = X_SIZE;
//        y_size = Y_SIZE;
    }

    //destructor
    ~WindyGridWorld(){};

    // size of grid world
    int x_size;
    int y_size;


    // Windfield (only y-component) !!! NOT YET MODULAR !!
    const int windPattern [10] = {0,0,0,1,1,1,2,2,1,0};
    //const int windPattern [10] = {0,0,0,0,0,0,0,0,0,0};

    // Accessor function in class windygridworld
    // double getReward(int new_x_pos_, int new_y_pos);
    int get_x_size();
    int get_y_size();

};

#endif // WINDYGRIDWORLD_H

