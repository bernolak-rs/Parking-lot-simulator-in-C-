#pragma once
#include "ParkingLot.h"
#include <cstddef>
#include <expected>
#include <optional>

enum class SpotType {
    Standard,
    Motorcycle,
    Electric,
    Disabled,
    Large
};

enum class ParkingError {
    Full,
    Occupied,
    InvalidSpot
};

class ParkingSpot {
private:
    size_t id;
    SpotType type;
    bool occupied;
    std::optional<int> vehicleId;
public:
    bool isOccupied() { return this->occupied; };
    std::expected<bool, ParkingError> occupy(int vehicleId) { 
        if (occupied) return std::unexpected(ParkingError::Occupied);
        this->vehicleId = vehicleId;
        this->occupied = true;
        return true;
    };
    void release() { 
        this->occupied = false; 
        this->vehicleId = std::nullopt;
    };
};