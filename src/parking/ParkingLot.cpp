#include "ParkingLot.h"

std::optional<int> ParkingLot::findSpot(const Vehicle& vehicle, ) {
    
};

/** Reserve parking spot */
// bool ParkingLot::reserveSpot(int spotId, int vehicleId) {

// };

void ParkingLot::releaseSpot(int spotId) {
    this->spots.at(spotId).release();
};

/** Return occupacy of parking lot 0-1 */
double ParkingLot::occupacyRate() const {
    return static_cast<double>(this->size) 
            / static_cast<double>(this->capacity);
};