#ifndef BT_DOOR_H
#define BT_DOOR_H

#include "bt_structure.h"

namespace BT_door
{

struct DoorStatus
{
    enum BT_Structure::Status doorIsOpen;
    int distanceToDoor;
};


struct CheckIfDoorIsOpenTask : public BT_Structure::Node
{  // Each task will be a struct (derived from Node of course).

    public:
        CheckIfDoorIsOpenTask (DoorStatus* status)
            :status(status)
        {}

        virtual enum BT_Structure::Status update() override
        {
            if (status->doorIsOpen == BT_Structure::BH_SUCCES)
            {std::cout << "The person sees that the door is open." << std::endl;  // will return true
                status->doorIsOpen = BT_Structure::BH_SUCCES;}
            else
            std::cout << "The person sees that the door is closed." << std::endl;  // will return false

            return BT_Structure::BH_FAILURE;
        }
private:
    DoorStatus* status;
};


struct ApproachDoorTask : public BT_Structure::Node
{
    private:
        DoorStatus* status;
        bool obstructed;
    public:
        ApproachDoorTask (DoorStatus* status, bool obstructed) : status(status), obstructed(obstructed)
        {}
        virtual enum BT_Structure::Status update() override
        {
            if (obstructed)
                return BT_Structure::BH_FAILURE;
            if (status->distanceToDoor > 0)
            {
                std::cout << "The person approaches the door." << std::endl;
                status->distanceToDoor--;  // thus run() is not a const function
                if (status->distanceToDoor > 1)
                    std::cout << "The person is now " << status->distanceToDoor << " meters from the door." << std::endl;
                else if (status->distanceToDoor == 1)
                    std::cout << "The person is now only one meter away from the door." << std::endl;
                else
                    std::cout << "The person is at the door." << std::endl;
            }
            return BT_Structure::BH_SUCCES;
        }
};

struct OpenDoorTask : public BT_Structure::Node
{
    private:
        DoorStatus* status;
    public:
        OpenDoorTask (DoorStatus* status) : status(status)
        {}
        virtual enum BT_Structure::Status update() override
        {
            if (status->distanceToDoor > 0)
            {
                std::cout << "The person is still too far away from the door.  He cannot open the door." << std::endl;
                return BT_Structure::BH_FAILURE;
            }
            status->doorIsOpen = BT_Structure::BH_SUCCES;  // run() not const because of this too
            std::cout << "The person opens the door." << std::endl;
            return BT_Structure::BH_SUCCES;
        }
};

};

#endif // BT_DOOR_H
