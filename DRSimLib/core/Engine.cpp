#include "include/drsim/Engine.h"
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <spdlog/spdlog.h>

namespace drsim {

Engine::Engine(const boost::posix_time::ptime& startTime)
    : time(startTime)
    , events()
    , eventIterators()
    , idCounter(0) {
}

void Engine::run() {
    while (!events.empty()) {
        step();
    }
}

void Engine::runUntil(const boost::posix_time::ptime& end) {
    while (!events.empty() && events.begin()->get()->getExecutionTime() <= end) {
        step();
    }
}

void Engine::step() {
    Event& event = *events.begin()->get();
    spdlog::trace("Processing event {}", event.getId());
    if (event.getExecutionTime() < time) {
        throw std::exception("Cannot go back in time");
    }
    if (event.getExecutionTime() > time) {
        time = event.getExecutionTime();
        notifyTimeObservers();
    }
    event.execute();
    remove(event);
}

const Event* Engine::add(std::unique_ptr<Event>& event) {
    event.get()->setId(idCounter++);
    spdlog::trace("Adding event {}", event.get()->getId());
    auto insertion = events.emplace(std::move(event));
    eventIterators.emplace(std::make_pair(insertion.first->get()->getId(), insertion.first));
    return insertion.first->get();
}

const Event* Engine::peek() {
    return events.begin()->get();
}

void Engine::remove(const Event& event) {
    const auto id = event.getId();
    spdlog::trace("Removing event {}", id);
    events.erase(eventIterators.at(id));
    eventIterators.erase(id);
}

const boost::posix_time::ptime& Engine::getTime() const {
    return time;
}

} // namespace drsim
