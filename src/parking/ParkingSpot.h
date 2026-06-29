#pragma once
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
    ParkingSpot(size_t id, SpotType type)
        : id(id), type(type), occupied(false), vehicleId(std::nullopt) {};
    size_t getId() { return this->id; };
    bool isOccupied() const { return this->occupied; };
    SpotType getType() const { return this->type; };
    std::expected<bool, ParkingError> occupy(int vehicleId); 
    void release() { 
        this->occupied = false; 
        this->vehicleId = std::nullopt;
    };
};