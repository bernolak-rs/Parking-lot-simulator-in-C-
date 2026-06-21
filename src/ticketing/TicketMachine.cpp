#include "TicketMachine.h"

Ticket TicketMachine::issueTicket(std::string vehicleTag, int currentTime) {
    Ticket ticket{ 
        id_seq, 
        vehicleTag, 
        std::chrono::system_clock::now(),
        std::nullopt
    };
};