#include "ParkingLot.h"

std::optional<int> findSpot(const Vehicle& vehicle);
bool reserveSpot(int spotId, int vehicleId);
void releaseSpot(int spotId);
double occupacyRate() const;