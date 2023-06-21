#pragma once
#include "Event.h"
#include "EventComparator.h"
#include "TimeProvider.h"
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/special_values_formatter.hpp>
#include <chrono>
#include <map>
#include <memory>
#include <random>
#include <set>

namespace drsim {

class Engine : public TimeProvider {
public:
    Engine(const boost::posix_time::ptime& startTime);

    void run();
    void runUntil(const boost::posix_time::ptime& end);
    void step();
    const Event* add(std::unique_ptr<Event>& event);
    const Event* peek();
    void remove(const Event& event);
    const boost::posix_time::ptime& getTime() const override;

    void operator=(const Engine& e) = delete;
    Engine(const Engine& e) = delete;

private:
    boost::posix_time::ptime time;

    std::set<std::unique_ptr<Event>, EventComparator> events;
    std::map<int, std::set<std::unique_ptr<Event>>::iterator> eventIterators;

    int idCounter;
};

} // namespace drsim
