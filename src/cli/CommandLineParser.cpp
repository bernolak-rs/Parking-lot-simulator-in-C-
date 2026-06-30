#include "CommandLineParser.h"

#include "../vehicles/VehicleState.h"

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
    std::vector<std::string> splitCsvLine(const std::string& line) {
        std::vector<std::string> fields;
        std::stringstream stream(line);
        std::string field;

        while (std::getline(stream, field, ',')) {
            fields.push_back(field);
        }

        if (!line.empty() && line.back() == ',') {
            fields.emplace_back();
        }

        return fields;
    }

    std::optional<VehicleType> parseVehicleType(const std::string& value) {
        if (value == "Car") return VehicleType::Car;
        if (value == "Motorcycle") return VehicleType::Motorcycle;
        if (value == "Van") return VehicleType::Van;
        if (value == "ElectricCar") return VehicleType::ElectricCar;
        if (value == "DisabledDriver") return VehicleType::DisabledDriver;

        return std::nullopt;
    }

    size_t parseSize(const std::string& value, const std::string& optionName) {
        try {
            return static_cast<size_t>(std::stoul(value));
        } catch (const std::exception&) {
            throw std::invalid_argument("Invalid value for " + optionName + ": " + value);
        }
    }

    c_time timeFromMinutes(size_t minutes) {
        return c_time{} + std::chrono::minutes(minutes);
    }
}

SimulationConfig CommandLineParser::parse(int argc, char* argv[]) {
    SimulationConfig config;

    for (int i = 1; i < argc; ++i) {
        std::string option = argv[i];

        if (option == "--help" || option == "-h") {
            printUsage(argv[0]);
            std::exit(0);
        }

        if (i + 1 >= argc) {
            throw std::invalid_argument("Missing value for option: " + option);
        }

        std::string value = argv[++i];

        if (option == "--cars") {
            config.carsFile = value;
        } else if (option == "--standard") {
            config.standardSpots = parseSize(value, option);
        } else if (option == "--motorcycle") {
            config.motorcycleSpots = parseSize(value, option);
        } else if (option == "--electric") {
            config.electricSpots = parseSize(value, option);
        } else if (option == "--disabled") {
            config.disabledSpots = parseSize(value, option);
        } else if (option == "--large") {
            config.largeSpots = parseSize(value, option);
        } else {
            throw std::invalid_argument("Unknown option: " + option);
        }
    }

    return config;
}

bool CommandLineParser::loadEvents(const std::string& filePath, SimulationEngine& engine) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Could not open cars file: " << filePath << "\n";
        return false;
    }

    std::string line;
    std::getline(file, line);

    size_t lineNumber = 1;
    while (std::getline(file, line)) {
        ++lineNumber;

        if (line.empty()) {
            continue;
        }

        auto fields = splitCsvLine(line);
        if (fields.size() != 6) {
            std::cerr << "Invalid CSV row at line " << lineNumber << "\n";
            return false;
        }

        size_t timeMinutes = parseSize(fields.at(0), "time_min");
        const auto& eventName = fields.at(1);
        int vehicleId = static_cast<int>(parseSize(fields.at(2), "vehicle_id"));
        const auto& tag = fields.at(3);
        auto vehicleType = parseVehicleType(fields.at(4));

        if (!vehicleType.has_value()) {
            std::cerr << "Invalid vehicle type at line " << lineNumber << ": "
                      << fields.at(4) << "\n";
            return false;
        }

        auto time = timeFromMinutes(timeMinutes);

        if (eventName == "arrival") {
            Vehicle vehicle(tag, vehicleType.value(), VehicleState::Arriving, nullptr);
            engine.scheduleArrival(time, vehicle, vehicleId);
        } else if (eventName == "departure") {
            if (fields.at(5).empty()) {
                std::cerr << "Missing spot_index for departure at line " << lineNumber << "\n";
                return false;
            }

            int spotIndex = static_cast<int>(parseSize(fields.at(5), "spot_index"));
            engine.scheduleDeparture(time, spotIndex);
        } else {
            std::cerr << "Invalid event at line " << lineNumber << ": " << eventName << "\n";
            return false;
        }
    }

    return true;
}

void CommandLineParser::printUsage(const char* programName) {
    std::cout
        << "Usage: " << programName << " [options]\n\n"
        << "Options:\n"
        << "  --cars FILE          CSV file with simulation events (default: cars.csv)\n"
        << "  --standard N         Number of standard spots (default: 10)\n"
        << "  --motorcycle N       Number of motorcycle spots (default: 3)\n"
        << "  --electric N         Number of electric spots (default: 3)\n"
        << "  --disabled N         Number of disabled spots (default: 2)\n"
        << "  --large N            Number of large spots (default: 2)\n"
        << "  --help, -h           Show this help\n";
}
