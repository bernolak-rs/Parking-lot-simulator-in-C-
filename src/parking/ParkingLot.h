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

    public:
        ParkingLot(size_t standardSpots, size_t motorcycleSpots,
           size_t electricSpots, size_t disabledSpots,
           size_t largeSpots);
        std::optional<int> findSpot(const Vehicle& vehicle);
        bool reserveSpot(int spotIndex, int vehicleId);
        void releaseSpot(int spotIndex);
        double occupacyRate() const;
        void addSpot(SpotType type);
};