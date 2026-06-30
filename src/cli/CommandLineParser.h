#pragma once

#include "../simulation/SimulationEngine.h"

#include <cstddef>
#include <string>

struct SimulationConfig {
    std::string carsFile = "cars.csv";
    size_t standardSpots = 10;
    size_t motorcycleSpots = 3;
    size_t electricSpots = 3;
    size_t disabledSpots = 2;
    size_t largeSpots = 2;
};

class CommandLineParser {
public:
    static SimulationConfig parse(int argc, char* argv[]);
    static bool loadEvents(const std::string& filePath, SimulationEngine& engine);
    static void printUsage(const char* programName);
};
