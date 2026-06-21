#pragma once
#include <optional>

enum class SpotType {
    Standard,
    Motorcycle,
    Electric,
    Disabled,
    Large
};

class ParkingSpot {
private:
    int id;
    SpotType type;
    bool occupied;
    std::optional<int> vehicleId;
};