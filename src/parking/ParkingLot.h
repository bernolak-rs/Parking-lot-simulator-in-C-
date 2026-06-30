#pragma once
#include <cstddef>
#include <optional>
#include "../vehicles/Vehicle.h"
#include <vector>
#include <unordered_map>
#include <queue>

#include "ParkingSpot.h"

class ParkingLot {
    private:
        size_t capacity; // Max capacity
        size_t size; // Taken spots
        std::vector<ParkingSpot> spots;
        std::unordered_map<SpotType, std::queue<int>> availableSpots;

        void addSpot(SpotType type);
        std::optional<int> findSpot(const Vehicle& vehicle);
        bool reserveSpot(int spotIndex, int vehicleId);
        
    public:
        ParkingLot(size_t standardSpots, size_t motorcycleSpots,
           size_t electricSpots, size_t disabledSpots,
           size_t largeSpots);
        bool releaseSpot(int spotIndex);
        double occupancyRate() const;
        std::optional<int> parkVehicle(const Vehicle& vehicle, int vehicleId);
        size_t getCapacity() const { return capacity; }
        size_t getOccupiedCount() const { return size; }
};
