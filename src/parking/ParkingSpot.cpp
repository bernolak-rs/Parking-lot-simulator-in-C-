#include "ParkingSpot.h"

std::expected<bool, ParkingError> ParkingSpot::occupy(int vehicleId) { 
        if (occupied) return std::unexpected(ParkingError::Occupied);
        this->vehicleId = vehicleId;
        this->occupied = true;
        return true;
};