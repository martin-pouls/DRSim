# DRSim (**D**ynamic **R**ide-Sharing **Sim**ulation)
This project is a discrete-event simulation for dynamic ride-sharing services implemented in C++. It is a result of my dissertation on [Real-Time Optimization for Dynamic Ride-Sharing](https://doi.org/10.5445/IR/1000158636). The main goal of this project is to enable users to evaluate their planning algorithms for vehicle routing and repositioning. For this purpose, the simulation can be coupled with a planning service via an API.

## Building the project
The project uses [CMake](https://cmake.org/) and the following third-party dependencies:
- [Boost.Date_Time](https://www.boost.org/doc/libs/1_75_0/doc/html/date_time.html)
- [spdlog](https://github.com/gabime/spdlog)
- [nlohmann/json](https://github.com/nlohmann/json)
- [GoogleTest](https://github.com/google/googletest)

These instructions assume that you are using Windows and [vcpkg](https://github.com/microsoft/vcpkg) for dependency management. To build the project and run the unit tests, install the dependencies listed above and subsequently execute the following commands:

```bat
mkdir .\build
cd .\build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\your\vcpkg.cmake 
cmake --build .
.\DRSimTest\Debug\DrSimTest.exe
```

## Using the simulation
The main entry point for using the simulation is `drsim::Simulation` in `Simulation.h`.

### Input
The simulation needs the following inputs.

#### Scenario
The simulation scenario is described in `Scenario.h`. It contains the following information:
- Start and end of the scenario.
- A startup duration (e.g. 6 hours). This defines the simulated time after which `PlanningServiceInterface::finishStartup()` is called. The main purpose is to reset gathered statistics for computational evaluations in the planning service. Otherwise, the collected performance indicators may be distorted by the initially empty system state.
- Trip requests that are replayed by the simulation.
- A vehicle fleet that serves these trip requests.

#### PlanningServiceInterface
`drsim::PlanningServiceInterface` defines the API between the simulation and a planning service for vehicle routing and repositioning. Developers wishing to use this simulation may implement this interface.

#### RoutingEngineInterface
`drsim::RoutingEngineInterface` defines the API for calculating routes on the road network and is used to obtain routes for realistic vehicle movements. Developers may either implement their own routing solver or provide a minimal wrapper around open-source solutions such as [RoutingKit](https://github.com/RoutingKit/RoutingKit) or [OSRM](https://github.com/Project-OSRM/osrm-backend).

### Output
Via `Simulation::writeSimulationLog(const std::string& outputFolder)`, the simulation can write some log files that can be used with our [DRSim-Viewer](). The output files have the following formats:

#### vehicleMovementReplay.csv
This file contains all vehicle movements.

| vehicleId | startTime | endTime | startLat | startLon | endLat | endLon |
|-----------|-----------|---------|----------|----------|--------|--------|
|0          |0          |5        |53.5478   |10.0089   |53.5478 |10.0089 |

#### requestReplay.csv
This file contains information regarding trip requests.

| requestId | time | state | 
|-----------|------|-------|
|0          |0     |A      |
|0          |100   |P      |
|0          |200   |D      |
|1          |300   |R      |

The following states are possible: **A**ccepted, **R**ejected, **P**icked up, and **D**ropped off.

#### simulation.json
This file contains some metadata concerning the simulation run. All timestamps in other files are seconds from the start.

```json
{
    "start": "20190319T180000",
    "end": "20190319T183000"
}
```

#### vehicleStatesReplay.csv
This file contains changes in vehicle states.

| vehicleId | time | state | 
|-----------|------|-------|
|0          |0     |I      |
|0          |100   |A      |
|0          |200   |R      |

The following states are possible: **I**dle, **A**ctive (i.e. serving a tour), and **R**epositioning.

#### simulationStats.json
This file contains aggregated statistics regarding vehicles and trip requests.

```json
{
    "requestStats": {
        "acceptedRequests": 42,
        "rejectedRequests": 5,
        "delay": {
            "buckets": [0, 60, 120],
            "counts": [21, 21]
        },
        "rideTime": {
            "buckets": [0, 180, 360, 540, 720],
            "counts": [10, 12, 11, 9]
        },
        "waitingTime": {
            "buckets": [0, 60, 120, 180, 240, 300],
            "counts": [7, 13, 10, 8, 4]
        }
    },
    "vehicleStats": {
        "activeCounts": [0, 2, 2],
        "idleCounts": [3, 0, 1],
        "repositioningCounts": [0, 1, 0],
        "timeStamps": ["20190319T180000", "20190319T180500", "20190319T181000"],
        "totalVehicles": 90
    }
}
```
The fields `requestStats.delay`, `requestStats.rideTime` and `requestStats.waitingTime` contain histogram data for the delay (compared to direct travel), the ride time (inside a vehicle) and the waiting time (between request submission and pickup) of trip requests.

## Viewer
The output described above may be loaded into [DRSim-Viewer](https://github.com/martin-pouls/DRSim-Viewer). The viewer offers a replay functionality and charts.

### Replay
Load `vehicleMovementReplay.csv`, `vehicleStatesReplay.csv`, `vehicleStatesReplay.csv` and `simulation.json` to view a replay of a simulation run.

![Import process](https://i.imgur.com/DAccDWT.gif)

### Charts
Load `simulationStats.json` to view visualize aggregated statistics regarding a simulation run.

![Charts view](https://i.imgur.com/REvYcDF.png)