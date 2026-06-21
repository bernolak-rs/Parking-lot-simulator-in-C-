#pragma once
#include "Ticket.h"

class TicketMachine {
private:
    size_t id_seq = 1;

public:
    Ticket issueTicket(std::string vehicleTag, int currentTime);
};