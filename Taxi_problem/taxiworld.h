#ifndef TAXIWORLD_H
#define TAXIWORLD_H



class TaxiWorld
{
public:
    TaxiWorld()
        : TaxiWorld(5,5)
    {}
    TaxiWorld(int Y_SIZE)
        : TaxiWorld(Y_SIZE,5)
    {}
    TaxiWorld(int Y_SIZE, int X_SIZE)
        : x_size(X_SIZE),
          y_size(Y_SIZE)
    {};

    int x_size;
    int y_size;


};


#endif // TAXIWORLD_H
