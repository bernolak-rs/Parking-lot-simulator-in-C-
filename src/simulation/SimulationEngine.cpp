#include "SimulationEngine.h"
#include "ticketing/Ticket.h"
#include "vehicles/Vehicle.h"
#include <optional>

SimulationEngine::SimulationEngine (
    ParkingLot& parkingLot,
    TicketMachine& ticketMachine,
    Barrier& entryBarrier,
    Barrier& exitBarrier
) : parkingLot(parkingLot), 
    ticketMachine(ticketMachine),
    entryBarrier(entryBarrier), 
    exitBarrier(exitBarrier) {
};

std::optional<int> SimulationEngine::handleVehicleArrival(Vehicle& vehicle, int vehicleId) {
    if (!entryBarrier.requestOpen()) {
        ++rejectedVehicles;
        return std::nullopt;
    }

    auto spotIndex = parkingLot.parkVehicle(vehicle, vehicleId);
    entryBarrier.close();

    if (!spotIndex.has_value()) {
        ++rejectedVehicles;
        return std::nullopt;
    }
    ++parkedVehicles;
    return spotIndex;
};

bool SimulationEngine::handleVehicleDeparture(int spotIndex) {
    if (!exitBarrier.requestOpen()) return false;

    bool released = parkingLot.releaseSpot(spotIndex);
    exitBarrier.close();
    if (released) {
        ++departedVehicles;
    }
    return released;
};

void SimulationEngine::scheduleArrival(c_time time, Vehicle vehicle, int vehicleId) {
    events.push(Event {
        time, 
        EventType::VehicleArrival,
        vehicle, 
        vehicleId, 
        std::nullopt
    });
};

void SimulationEngine::scheduleDeparture(c_time time, int spotIndex) {
    events.push(Event{
        time,
        EventType::VehicleDeparture,
        Vehicle("", 
            VehicleType::Car, 
            VehicleState::Exited, 
            nullptr),
        -1,
        spotIndex
    });
}

void SimulationEngine::run() {
    while (!events.empty()) {
        Event event = events.top();
        events.pop();
        
        switch (event.type) {
            case EventType::VehicleArrival:
                handleVehicleArrival(event.vehicle, event.vehicleId);
                break;
            case EventType::VehicleDeparture:
                if (event.spotIndex.has_value()) {
                    handleVehicleDeparture(event.spotIndex.value());
                }
                break;
        }
    }
};