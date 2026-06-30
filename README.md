# Parking Lot Simulator in C++

Application that simulates parking garage work flow.

## Requirements

- CMake 3.16+
- A C++23 compiler, such as `clang++`

## Build

```bash
cmake --build build
```

## Run

Run the simulator with the sample CSV:

```bash
./build/ParkFlowPlusPlus --cars cars.csv
```

You can also configure parking spot counts:

```bash
./build/ParkFlowPlusPlus \
  --cars cars.csv \
  --standard 10 \
  --motorcycle 3 \
  --electric 3 \
  --disabled 2 \
  --large 2
```

Available options:

```text
--cars FILE          CSV file with simulation events
--standard N         Number of standard spots
--motorcycle N       Number of motorcycle spots
--electric N         Number of electric spots
--disabled N         Number of disabled spots
--large N            Number of large spots
--help, -h           Show help
```

If cars flag is not provided defaults to cars.csv

## CSV Input

The simulator reads events from a CSV file with this header:

```csv
time_min,event,vehicle_id,tag,vehicle_type,spot_index
```

Columns:

- `time_min`: minutes from simulation start
- `event`: `arrival` or `departure`
- `vehicle_id`: unique vehicle id
- `tag`: license plate
- `vehicle_type`: `Car`, `Motorcycle`, `ElectricCar`, `DisabledDriver`, or `Van`
- `spot_index`: required for `departure`, empty for `arrival`

Example:

```csv
time_min,event,vehicle_id,tag,vehicle_type,spot_index
0,arrival,1,BA123AA,Car,
15,departure,1,BA123AA,Car,0
```

## Tests

Build and run all tests:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

Run a specific test executable:

```bash
./build/ParkingLotTests
./build/SimulationEngineTests
```
