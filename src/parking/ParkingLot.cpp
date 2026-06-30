#include "ParkingLot.h"
#include "ParkingSpot.h"
#include <cstddef>
#include <iostream>
#include <optional>

ParkingLot::ParkingLot(size_t standardSpots, size_t motorcycleSpots,
           size_t electricSpots, size_t disabledSpots,
           size_t largeSpots)
    : capacity(0), size(0) {
    availableSpots[SpotType::Standard];
    availableSpots[SpotType::Motorcycle];
    availableSpots[SpotType::Electric];
    availableSpots[SpotType::Disabled];
    availableSpots[SpotType::Large];

    for (size_t i = 0; i < standardSpots; ++i) {
        addSpot(SpotType::Standard);
    }

    for (size_t i = 0; i < motorcycleSpots; ++i) {
        addSpot(SpotType::Motorcycle);
    }

    for (size_t i = 0; i < electricSpots; ++i) {
        addSpot(SpotType::Electric);
    }

    for (size_t i = 0; i < disabledSpots; ++i) {
        addSpot(SpotType::Disabled);
    }

    for (size_t i = 0; i < largeSpots; ++i) {
        addSpot(SpotType::Large);
    }
};

std::optional<int> ParkingLot::parkVehicle(const Vehicle& vehicle, int vehicleId) {
    auto spotIndex = findSpot(vehicle);

    if (!spotIndex.has_value()) {
        return std::nullopt;
    }
    if (!reserveSpot(spotIndex.value(), vehicleId)) {
        return std::nullopt;
    }

    return spotIndex;
};

std::optional<int> ParkingLot::findSpot(const Vehicle& vehicle) {
    SpotType spotType;

    switch (vehicle.getType()) {
        case VehicleType::ElectricCar:
            spotType = SpotType::Electric;
            break;
        case VehicleType::DisabledDriver:
            spotType = SpotType::Disabled;
            break;
        case VehicleType::Van:
            spotType = SpotType::Large;
            break;
        case VehicleType::Motorcycle:
            spotType = SpotType::Motorcycle;
            break;
        case VehicleType::Car:
        default:
            spotType = SpotType::Standard;
            break;
    }

    auto& queue = availableSpots.at(spotType);

    while (!queue.empty()) {
        int index = queue.front();

        if (index >= 0 && index < static_cast<int>(spots.size()) &&
            !spots.at(index).isOccupied()) {
            return index;
        }
        queue.pop();
    }
    return std::nullopt;
};

/** Reserve parking spot */
bool ParkingLot::reserveSpot(int spotIndex, int vehicleId) {
    auto& spot = this->spots.at(spotIndex);
    auto result = spot.occupy(vehicleId);

    if (!result.has_value()) {
        std::cerr << "Spot " << spotIndex << "is unavailable.";
        return false;
    }

    auto spotType = spot.getType();
    auto& available = this->availableSpots.at(spotType);

    if (!available.empty() && available.front() == spotIndex) {
        available.pop();
    }

    ++size;
    return true;
};

bool ParkingLot::releaseSpot(int spotIndex) {
    if (spotIndex < 0 || spotIndex >= static_cast<int>(this->spots.size())) {
        std::cerr << "Spot index " << spotIndex << " is out of bounds.\n";
        return false;
    }
    auto& spot = this->spots.at(spotIndex);

    if (!spot.isOccupied()) {
        std::cerr << "Spot " << spotIndex << " is already empty\n";
        return false;
    }

    SpotType spotType = spot.getType();
    spot.release();
    this->availableSpots.at(spotType).push(spotIndex);
    --this->size;
    return true;
};

/** Return occupacy of parking lot 0-1 */
double ParkingLot::occupancyRate() const {
    return static_cast<double>(this->size) 
            / static_cast<double>(this->capacity);
};

void ParkingLot::addSpot(SpotType type) {
    auto index = static_cast<int>(this->spots.size());

    spots.emplace_back(index, type);
    availableSpots.at(type).push(index);
    ++capacity;
};
