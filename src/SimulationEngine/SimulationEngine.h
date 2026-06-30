#pragma once
#include "barriers/Barrier.h"
#include "parking/ParkingLot.h"
#include "ticketing/Ticket.h"
#include "ticketing/TicketMachine.h"
#include "vehicles/Vehicle.h"
#include <optional>
#include <queue>
#include <vector>

enum class EventType {
    VehicleArrival,
    VehicleDeparture
};

struct Event {
    c_time timeStamp;
    EventType type;
    Vehicle vehicle;
    int vehicleId;
    std::optional<int> spotIndex;
};

struct EventCompare {
    bool operator() (const Event& x, const Event& y) const {
        return x.timeStamp > y.timeStamp;
    }
};

class SimulationEngine {
private:
    ParkingLot& parkingLot;
    TicketMachine& ticketMachine;
    Barrier& entryBarrier;
    Barrier& exitBarrier;

    std::priority_queue<Event, std::vector<Event>, EventCompare> events;
    
    size_t parkedVehicles = 0;
    size_t rejectedVehicles = 0;
    size_t departedVehicles = 0;

public:
    SimulationEngine(
        ParkingLot& parkingLot,
        TicketMachine& ticketMachine,
        Barrier& entryBarrier,
        Barrier& exitBarrier
    );

    std::optional<int> handleVehicleArrival(Vehicle& vehicle, int vehicleId);
    bool handleVehicleDeparture(int spotIndex);

    void scheduleArrival(c_time time, Vehicle vehicle, int vehicleId);
    void scheduleDeparture(c_time time, int spotIndex);
    void run();

    size_t getParkedVehicles() const { return parkedVehicles; }
    size_t getRejectedVehicles() const { return rejectedVehicles; }
    size_t getDepartedVehicles() const { return departedVehicles; }
};