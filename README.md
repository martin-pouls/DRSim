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

#### movementLog.csv
This file contains all vehicle movements.

| vehicleId | startTime | endTime | startLat | startLon | endLat | endLon |
|-----------|-----------|---------|----------|----------|--------|--------|
|0          |0          |5        |53.5478   |10.0089   |53.5478 |10.0089 |

#### requestLog.csv
This file contains information regarding trip requests.

| requestId | time | state | 
|-----------|------|-------|
|0          |0     |A      |
|0          |100   |P      |
|0          |200   |D      |
|1          |300   |R      |

The following states are possible: **A**ccepted, **R**ejected, **P**icked up, and **D**ropped off.

#### simulationLog.json
This file contains some metadata concerning the simulation run. All timestamps in other files are seconds from the start.

```json
{
    "start": "20190319T180000",
    "end": "20190319T183000"
}
```

#### vehicleStatesLog.csv
This file contains changes in vehicle states.

| vehicleId | time | state | 
|-----------|------|-------|
|0          |0     |I      |
|0          |100   |A      |
|0          |200   |R      |

The following states are possible: **I**dle, **A**ctive (i.e. serving a tour), and **R**epositioning.

## Viewer
The output described above may be loaded into [DRSim-Viewer](https://github.com/martin-pouls/DRSim-Viewer) to replay a simulation run.

![Import process](https://i.imgur.com/DAccDWT.gif)