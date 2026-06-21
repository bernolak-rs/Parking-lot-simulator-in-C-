#pragma once
#include <optional>
#include <../vehicles/Vehicle.h>
#include <vector>
#include <unordered_map>
#include <queue>

#include "ParkingSpot.h"

class ParkingLot {
    private:
        size_t capacity;
        size_t size;
        std::vector<ParkingSpot> spots;
        std::unordered_map<SpotType, std::queue<int>> availableSpots;

    public:
        std::optional<int> findSpot(const Vehicle& vehicle);
        bool reserveSpot(int spotId, int vehicleId);
        void releaseSpot(int spotId);
        double occupacyRate() const;
};