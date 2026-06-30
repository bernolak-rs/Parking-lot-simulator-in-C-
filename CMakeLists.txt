cmake_minimum_required(VERSION 3.16)
project(ParkFlowPlusPlus)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ParkFlowPlusPlus
    src/main.cpp
    src/cli/CommandLineParser.cpp
    src/simulation/SimulationEngine.cpp
    src/parking/ParkingLot.cpp
    src/parking/ParkingSpot.cpp
    src/barriers/Barrier.cpp
    src/ticketing/TicketMachine.cpp
)

target_include_directories(ParkFlowPlusPlus PRIVATE src)

add_executable(ParkingLotTests
    tests/ParkingLotTests.cpp
    src/parking/ParkingLot.cpp
    src/parking/ParkingSpot.cpp
)

target_include_directories(ParkingLotTests PRIVATE src)

add_executable(SimulationEngineTests
    tests/SimulationEngineTests.cpp
    src/simulation/SimulationEngine.cpp
    src/parking/ParkingLot.cpp
    src/parking/ParkingSpot.cpp
    src/barriers/Barrier.cpp
    src/ticketing/TicketMachine.cpp
)

target_include_directories(SimulationEngineTests PRIVATE src)

add_executable(PaymentMachineTests
    tests/PaymentMachineTests.cpp
)

target_include_directories(PaymentMachineTests PRIVATE src)

enable_testing()

add_test(NAME ParkingLotTests COMMAND ParkingLotTests)
add_test(NAME SimulationEngineTests COMMAND SimulationEngineTests)
add_test(NAME PaymentMachineTests COMMAND PaymentMachineTests)
