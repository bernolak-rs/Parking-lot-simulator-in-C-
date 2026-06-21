#pragma once
#include <optional>
#include <chrono>
#include <string>

typedef std::chrono::system_clock::time_point c_time;

class Ticket {
private:
    int id;
    std::string vehicleTag;
    std::chrono::system_clock::time_point entryTime;
    std::optional<std::chrono::system_clock::time_point> exitTime;
    bool paid;
public:
    Ticket(
        int id,
        std::string vehicleTag,
        c_time entryTime,
        std::optional<std::chrono::system_clock::time_point> exitTime) : 
            id(id), 
            vehicleTag(vehicleTag), 
            entryTime(entryTime), 
            exitTime(exitTime), 
            paid(false) {};
    
    c_time getEntryTime() const { return this->entryTime; };
};