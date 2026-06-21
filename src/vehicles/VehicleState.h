#pragma once

enum class VehicleState {
    Arriving,
    WaitingAtEntry,
    TicketIssued,
    SearchingForSpot,
    Parked,
    Paying,
    WaitingAtExit,
    Exited
};