#include "barriers/Barrier.h"
#include "cli/CommandLineParser.h"
#include "parking/ParkingLot.h"
#include "simulation/SimulationEngine.h"
#include "ticketing/TicketMachine.h"

#include <exception>
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        auto config = CommandLineParser::parse(argc, argv);

        ParkingLot parkingLot(
            config.standardSpots,
            config.motorcycleSpots,
            config.electricSpots,
            config.disabledSpots,
            config.largeSpots
        );

        TicketMachine ticketMachine;
        Barrier entryBarrier;
        Barrier exitBarrier;
        SimulationEngine engine(parkingLot, ticketMachine, entryBarrier, exitBarrier);

        if (!CommandLineParser::loadEvents(config.carsFile, engine)) {
            return 1;
        }

        engine.run();

        std::cout << "\nSimulation finished\n"
                  << "Parked vehicles: " << engine.getParkedVehicles() << "\n"
                  << "Rejected vehicles: " << engine.getRejectedVehicles() << "\n"
                  << "Departed vehicles: " << engine.getDepartedVehicles() << "\n"
                  << "Occupied spots: " << parkingLot.getOccupiedCount()
                  << "/" << parkingLot.getCapacity() << "\n"
                  << "Occupancy rate: " << parkingLot.occupancyRate() << "\n";

        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n";
        CommandLineParser::printUsage(argv[0]);
        return 1;
    }
}
