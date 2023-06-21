#pragma once

namespace drsim {

class Constants {
public:
    static constexpr int VEHICLE_REMOVAL_EVENT_PRIORITY = 0;

    static constexpr int REQUEST_EVENT_PRIORITY = 1;

    static constexpr int REPOSITIONING_ARRIVAL_EVENT_PRIORITY = 2;

    static constexpr int SERVICE_START_EVENT_PRIORITY = 3;

    static constexpr int TOUR_STOP_ARRIVAL_EVENT_PRIORITY = 4;

    static constexpr int SERVICE_END_EVENT_PRIORITY = 5;

    static constexpr int RELOCATION_UPDATE_EVENT_PRIORITY = 6;

    static constexpr int TOUR_UPDATE_EVENT_PRIORITY = 7;

    static constexpr int GPS_EVENT_PRIORITY = 8;

    static constexpr int ARC_END_EVENT_PRIORITY = 9;

    static constexpr int VEHICLE_CREATION_EVENT_PRIORITY = 10;

    static constexpr int STARTUP_FINISH_EVENT_PRIORITY = 11;

    static constexpr int TIME_EVENT_PRIORITY = 11;
};

} // namespace drsim