#include "TicketMachine.h"

Ticket TicketMachine::issueTicket(std::string vehicleTag, int currentTime) {
    Ticket ticket{ 
        this->id_seq, 
        vehicleTag, 
        std::chrono::system_clock::now(),
        std::nullopt
    };
    this->id_seq++;
    return ticket;
};