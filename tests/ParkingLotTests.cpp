#include "../src/parking/ParkingLot.h"
#include "../src/vehicles/Vehicle.h"
#include "../src/vehicles/VehicleState.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <optional>
#include <sstream>

namespace {
Vehicle makeVehicle(VehicleType type) {
    return Vehicle("TEST", type, VehicleState::Arriving, nullptr);
}

void assertClose(double actual, double expected) {
    assert(std::fabs(actual - expected) < 0.000001);
}

void testFindSpotReturnsMatchingSpotTypes() {
    ParkingLot lot(1, 1, 1, 1, 1);

    assert(lot.findSpot(makeVehicle(VehicleType::Car)) == std::optional<int>(0));
    assert(lot.findSpot(makeVehicle(VehicleType::Motorcycle)) == std::optional<int>(1));
    assert(lot.findSpot(makeVehicle(VehicleType::ElectricCar)) == std::optional<int>(2));
    assert(lot.findSpot(makeVehicle(VehicleType::DisabledDriver)) == std::optional<int>(3));
    assert(lot.findSpot(makeVehicle(VehicleType::Van)) == std::optional<int>(4));
}

void testReserveMakesSpotUnavailable() {
    ParkingLot lot(1, 0, 0, 0, 0);
    auto car = makeVehicle(VehicleType::Car);

    auto spotIndex = lot.findSpot(car);
    assert(spotIndex.has_value());
    assert(lot.reserveSpot(spotIndex.value(), 100));

    assert(!lot.findSpot(car).has_value());
    assertClose(lot.occupacyRate(), 1.0);
}

void testReleaseMakesSpotAvailableAgain() {
    ParkingLot lot(1, 0, 0, 0, 0);
    auto car = makeVehicle(VehicleType::Car);

    auto spotIndex = lot.findSpot(car);
    assert(spotIndex.has_value());
    assert(lot.reserveSpot(spotIndex.value(), 100));

    lot.releaseSpot(spotIndex.value());

    assert(lot.findSpot(car) == spotIndex);
    assertClose(lot.occupacyRate(), 0.0);
}

void testReserveOccupiedSpotFails() {
    ParkingLot lot(1, 0, 0, 0, 0);
    auto car = makeVehicle(VehicleType::Car);

    auto spotIndex = lot.findSpot(car);
    assert(spotIndex.has_value());

    assert(lot.reserveSpot(spotIndex.value(), 100));

    std::ostringstream errorOutput;
    auto* originalErrorBuffer = std::cerr.rdbuf(errorOutput.rdbuf());
    assert(!lot.reserveSpot(spotIndex.value(), 200));
    std::cerr.rdbuf(originalErrorBuffer);

    assertClose(lot.occupacyRate(), 1.0);
}

void testUnavailableTypeReturnsNullopt() {
    ParkingLot lot(1, 0, 0, 0, 0);

    assert(!lot.findSpot(makeVehicle(VehicleType::Motorcycle)).has_value());
    assert(!lot.findSpot(makeVehicle(VehicleType::ElectricCar)).has_value());
    assert(!lot.findSpot(makeVehicle(VehicleType::DisabledDriver)).has_value());
    assert(!lot.findSpot(makeVehicle(VehicleType::Van)).has_value());
}
}

int main() {
    testFindSpotReturnsMatchingSpotTypes();
    testReserveMakesSpotUnavailable();
    testReleaseMakesSpotAvailableAgain();
    testReserveOccupiedSpotFails();
    testUnavailableTypeReturnsNullopt();

    std::cout << "ParkingLotTests passed\n";
    return 0;
}
