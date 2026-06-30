#include "../src/SimulationEngine/SimulationEngine.h"
#include "../src/barriers/Barrier.h"
#include "../src/parking/ParkingLot.h"
#include "../src/ticketing/TicketMachine.h"
#include "../src/vehicles/Vehicle.h"
#include "../src/vehicles/VehicleState.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <sstream>

namespace {
    Vehicle makeCar() {
        return Vehicle("BA123AA", VehicleType::Car, VehicleState::Arriving, nullptr);
    }

    c_time atMinute(int minute) {
        return c_time{} + std::chrono::minutes(minute);
    }

    struct CoutCapture {
        std::ostringstream output;
        std::streambuf* originalBuffer;

        CoutCapture() : originalBuffer(std::cout.rdbuf(output.rdbuf())) {}

        ~CoutCapture() {
            std::cout.rdbuf(originalBuffer);
        }
    };

    void testArrivalParksVehicle() {
        CoutCapture capture;
        ParkingLot lot(1, 0, 0, 0, 0);
        TicketMachine ticketMachine;
        Barrier entryBarrier;
        Barrier exitBarrier;
        SimulationEngine engine(lot, ticketMachine, entryBarrier, exitBarrier);

        engine.scheduleArrival(atMinute(10), makeCar(), 1);
        engine.run();

        assert(engine.getParkedVehicles() == 1);
        assert(engine.getRejectedVehicles() == 0);
        assert(engine.getDepartedVehicles() == 0);
        assert(lot.getOccupiedCount() == 1);
    }

    void testFullLotRejectsSecondVehicle() {
        CoutCapture capture;
        ParkingLot lot(1, 0, 0, 0, 0);
        TicketMachine ticketMachine;
        Barrier entryBarrier;
        Barrier exitBarrier;
        SimulationEngine engine(lot, ticketMachine, entryBarrier, exitBarrier);

        engine.scheduleArrival(atMinute(10), makeCar(), 1);
        engine.scheduleArrival(atMinute(20), makeCar(), 2);
        engine.run();

        assert(engine.getParkedVehicles() == 1);
        assert(engine.getRejectedVehicles() == 1);
        assert(engine.getDepartedVehicles() == 0);
        assert(lot.getOccupiedCount() == 1);
    }

    void testDepartureReleasesSpot() {
        CoutCapture capture;
        ParkingLot lot(1, 0, 0, 0, 0);
        TicketMachine ticketMachine;
        Barrier entryBarrier;
        Barrier exitBarrier;
        SimulationEngine engine(lot, ticketMachine, entryBarrier, exitBarrier);

        engine.scheduleArrival(atMinute(10), makeCar(), 1);
        engine.scheduleDeparture(atMinute(20), 0);
        engine.run();

        assert(engine.getParkedVehicles() == 1);
        assert(engine.getRejectedVehicles() == 0);
        assert(engine.getDepartedVehicles() == 1);
        assert(lot.getOccupiedCount() == 0);
    }

    void testEventsRunInTimestampOrder() {
        CoutCapture capture;
        ParkingLot lot(1, 0, 0, 0, 0);
        TicketMachine ticketMachine;
        Barrier entryBarrier;
        Barrier exitBarrier;
        SimulationEngine engine(lot, ticketMachine, entryBarrier, exitBarrier);

        engine.scheduleDeparture(atMinute(30), 0);
        engine.scheduleArrival(atMinute(10), makeCar(), 1);
        engine.run();

        assert(engine.getParkedVehicles() == 1);
        assert(engine.getDepartedVehicles() == 1);
        assert(lot.getOccupiedCount() == 0);
    }
}

int main() {
    testArrivalParksVehicle();
    testFullLotRejectsSecondVehicle();
    testDepartureReleasesSpot();
    testEventsRunInTimestampOrder();

    std::cout << "SimulationEngineTests passed\n";
    return 0;
}
