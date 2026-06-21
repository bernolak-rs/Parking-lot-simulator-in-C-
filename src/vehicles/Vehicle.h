#pragma once
#include "VehicleState.h"
#include "../ticketing/Ticket.h"
#include <string>

enum class VehicleType {
    Car,
    Motorcycle,
    Van,
    ElectricCar,
    DisabledDriver
};

class Vehicle {
    private:
        std::string tag;
        VehicleType type;
        VehicleState state;
        Ticket* ticket;
    public:
        Vehicle(
            std::string tag,
            VehicleType type,
            VehicleState state,
            Ticket* ticket
        ) : tag(tag), type(type), state(state), ticket(ticket) {};
};