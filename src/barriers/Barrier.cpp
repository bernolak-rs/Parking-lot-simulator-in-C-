#include "Barrier.h"
#include <iostream>

bool Barrier::requestOpen() {
    if (this->state == BarrierState::Open) {
        std::cout << "The barrier is already open.\n";
        return true;
    }
    if (this->state == BarrierState::Error) {
        return false;
    }
    std::cout << "Barrier is opening.\n";
    std::cout << "Barrier is open.\n";
    this->state = BarrierState::Open;
    return true;
};

bool Barrier::close() {
   if (this->state == BarrierState::Closed) {
        std::cout << "The barrier is already closed.\n";
        return true;
    }
    if (this->state == BarrierState::Error) {
        return false;
    }
    std::cout << "Barrier is closing.\n";
    std::cout << "Barrier is closed.\n";
    this->state = BarrierState::Closed;
    return true; 
};