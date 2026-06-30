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

    void testParkVehicleReturnsMatchingSpotTypes() {
        ParkingLot lot(1, 1, 1, 1, 1);

        assert(lot.parkVehicle(makeVehicle(VehicleType::Car), 100) == std::optional<int>(0));
        assert(lot.parkVehicle(makeVehicle(VehicleType::Motorcycle), 101) == std::optional<int>(1));
        assert(lot.parkVehicle(makeVehicle(VehicleType::ElectricCar), 102) == std::optional<int>(2));
        assert(lot.parkVehicle(makeVehicle(VehicleType::DisabledDriver), 103) == std::optional<int>(3));
        assert(lot.parkVehicle(makeVehicle(VehicleType::Van), 104) == std::optional<int>(4));
        assertClose(lot.occupancyRate(), 1.0);
    }

    void testParkVehicleMakesSpotUnavailable() {
        ParkingLot lot(1, 0, 0, 0, 0);
        auto car = makeVehicle(VehicleType::Car);

        auto spotIndex = lot.parkVehicle(car, 100);
        assert(spotIndex.has_value());

        assert(!lot.parkVehicle(car, 101).has_value());
        assertClose(lot.occupancyRate(), 1.0);
    }

    void testReleaseMakesSpotAvailableAgain() {
        ParkingLot lot(1, 0, 0, 0, 0);
        auto car = makeVehicle(VehicleType::Car);

        auto spotIndex = lot.parkVehicle(car, 100);
        assert(spotIndex.has_value());

        lot.releaseSpot(spotIndex.value());

        assert(lot.parkVehicle(car, 101) == spotIndex);
        lot.releaseSpot(spotIndex.value());
        assertClose(lot.occupancyRate(), 0.0);
    }

    void testReleaseAlreadyEmptySpotDoesNotChangeOccupancy() {
        ParkingLot lot(1, 0, 0, 0, 0);
        auto car = makeVehicle(VehicleType::Car);

        auto spotIndex = lot.parkVehicle(car, 100);
        assert(spotIndex.has_value());
        lot.releaseSpot(spotIndex.value());

        std::ostringstream errorOutput;
        auto* originalErrorBuffer = std::cerr.rdbuf(errorOutput.rdbuf());
        lot.releaseSpot(spotIndex.value());
        std::cerr.rdbuf(originalErrorBuffer);

        assertClose(lot.occupancyRate(), 0.0);
    }

    void testUnavailableTypeReturnsNullopt() {
        ParkingLot lot(1, 0, 0, 0, 0);

        assert(!lot.parkVehicle(makeVehicle(VehicleType::Motorcycle), 100).has_value());
        assert(!lot.parkVehicle(makeVehicle(VehicleType::ElectricCar), 101).has_value());
        assert(!lot.parkVehicle(makeVehicle(VehicleType::DisabledDriver), 102).has_value());
        assert(!lot.parkVehicle(makeVehicle(VehicleType::Van), 103).has_value());
        assertClose(lot.occupancyRate(), 0.0);
    }
}

int main() {
    testParkVehicleReturnsMatchingSpotTypes();
    testParkVehicleMakesSpotUnavailable();
    testReleaseMakesSpotAvailableAgain();
    testReleaseAlreadyEmptySpotDoesNotChangeOccupancy();
    testUnavailableTypeReturnsNullopt();

    std::cout << "ParkingLotTests passed\n";
    return 0;
}
